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

#pragma once

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>

class Ton
{
private:
    std::unordered_map<std::string, Ton*> keyvalues;
    static std::string ton2string(Ton* ton,int lvl);

public:

    //Member
    Ton();
    Ton(std::string key);
    ~Ton();

    //Capacity
    //bool empty()
    //size_t size()
    //max_size()

    //Iterators mayB?
    void getKeys(std::vector<std::string> &keys);

    //Element access, Modifiers
    Ton* at(std::string key); //TODO []
    void insert(std::string key); //TODO []
    void insert(std::string key,std::string value);
    // void erase(std::string key);

    //Element lookup
    bool containsKey(std::string key);

    //Static out
    std::string toString(); //TODO <<

    //Static in
    static Ton* parseFromFile(std::string fileName);
    static Ton* parseFromString(std::string raw);
    static Ton* parseFromString(std::istream &raw);

};