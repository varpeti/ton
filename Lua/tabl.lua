--[[ https://github.com/varpeti/tabl
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
]]


--Copy t1 table to t2 table
local function copytable(t1,t2,lvl)
    for k,v in pairs(t1) do
        if type(v)=="table" then
            t2[k]={}
            copytable(v,t2[k],lvl+1)
        else
            t2[k]=v
        end
    end
end

function table.copy(t1)
    local t2 = {}
    copytable(t1,t2,0)
    return t2
end

--Convert a table into a pretty string
local function table2string(data,lvl)
    local r = ""

    local t = ""
    for i=1,lvl do t = t.."\t" end

    if type(data)=="table" then
        for k,v in pairs(data) do
            r = r..t..tostring(k).."\n"..table2string(v,lvl+1)
        end
    else
        r = t..tostring(data).."\n"
    end
    return r
end

function table.toString(data)
    return table2string(data,0)
end