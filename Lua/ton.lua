--[[
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


local ton = {}

function ton.read(filename)
    file = io.open(filename, "r")
    local raw = file:read("*a")
    file:close()
    return ton.prase(raw)
end

local function split(inputstr, sep)
        sep = sep or "%s"
        local t = {}
        for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
            table.insert(t, str)
        end
        return t
end

function ton.prase(raw)
    local lines = split(raw,"\n")

    local stack = {}
    local hash  = {}

    local ret = {}
    
    local last = -1
    for i,line in ipairs(lines) do
        local t, value =  string.match(line,"^([\t ]*)([^\t ].*)$")
        t = t:len()
        --print(t,value)

        hash[t] = value

        if     t>last then
            table.insert(stack,t)
        elseif t<last then
            while #stack>0 and stack[#stack]>t do
                table.remove(stack,#stack)
            end
        else
        end
        last = t

        local a = ret
        for j,tt in ipairs(stack) do
            if not a[hash[tt]] then a[hash[tt]]={} end
            a = a[hash[tt]]
        end
    end
    return ret
end

return ton
