/*
MIT License

Copyright (c) 2018 Váraljai Péter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Ton/Ton.h"

//*/// Member

Ton::Ton()
{}

Ton::Ton(std::string key)
{
    this->insert(key);
}

Ton::~Ton() 
{
    //std::cout << this << "\n";
    for(auto it = keyvalues.begin(); it != keyvalues.end(); ++it)
    {
        delete it->second;
    }
    keyvalues.clear();
}

//*/// Iterators
void Ton::getKeys(std::vector<std::string> &keys)
{
    for(auto it = keyvalues.begin(); it != keyvalues.end(); ++it)
    {
        keys.push_back(it->first);
    }
}

//*/// Element access, Modifiers

Ton* Ton::at(std::string key)
{
    std::unordered_map<std::string,Ton*>::const_iterator got = keyvalues.find(key);
    if (got!=keyvalues.end()) return got->second;

    return nullptr;
}

void Ton::insert(std::string key)
{
    // If the key already exist don't overwrite
    if (!this->containsKey(key)) keyvalues[key]=new Ton();  
}

void Ton::insert(std::string key, std::string value)
{
    // If the key already exist insert another value
    if (!this->containsKey(key)) 
        keyvalues[key]=new Ton(value);
    else
        this->at(key)->insert(value);
}

//*/// Element lookup

bool Ton::containsKey(std::string key)
{
    return ( keyvalues.find(key)!=keyvalues.end() );
}

//*/// Static in

Ton* Ton::parseFromFile(std::string fileName)
{
    std::istream* s = new std::ifstream(fileName);
    Ton* ret = Ton::parseFromString(*s);
    delete s;
    return ret;
}

Ton* Ton::parseFromString(std::string raw)
{
    std::istream* s = new std::stringstream(raw);
    Ton* ret = Ton::parseFromString(*s);
    delete s;
    return ret;
}

Ton* Ton::parseFromString(std::istream &raw)
{
    Ton* ret = new Ton();

    std::vector<int> stack;
    std::unordered_map<int,std::string> hash;
    int last = -1;

    std::string line;
    while (std::getline(raw, line))
    {
        std::regex re("^([\t ]*)([^\t ].*)$");
        std::smatch match;
        std::regex_search(line, match, re);
        if (match.size() > 1) 
        {
            int t = match.str(1).length();
            std::string value = match.str(2);
            //std::cout << t << " " << value << "\n";

            hash[t]=value;

            if (t>last)
            {
                stack.push_back(t);
            }
            else if (t<last)
            {
                while (stack.size()>0 && stack.back()>t)
                {
                    stack.pop_back();
                }
            }
            last = t;

            Ton* a = ret;
            for(int tt : stack)
            {
                std::string key = hash[tt];
                a->insert(key);
                a = a->at(key);
                //std::cout << key << "\n";
            }
            //std::cout << "\n";
        }
    }

    return ret;
}

//*/// Static out

std::string Ton::ton2string(Ton* ton,int lvl)
{
    std::string ret;
    std::string t = std::string(lvl, '\t');

    for(auto it = ton->keyvalues.begin(); it != ton->keyvalues.end(); ++it)
    {
        ret+=(t+it->first+"\n"+ton2string(it->second,lvl+1)); //RECURSION!!!
    }

    return ret;
}

std::string Ton::toString()
{
    return Ton::ton2string(this,0);
}

