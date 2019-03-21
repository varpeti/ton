local ton = require("ton")
require("tabl") -- toString

local eq1 = ton.read("testEQ1.ton")
local s1  = table.toString(eq1)

local eq2 = ton.read("testEQ2.ton")
local s2  = table.toString(eq2)

local function split(inputstr, sep)
        sep = sep or "%s"
        local t = {}
        for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
            table.insert(t, str)
        end
        return t
end

-- Assert that every data in eq1 can be found in eq2
local eq1 = split(s1,"\n")
local eq2 = split(s2,"\n")
for i1,v1 in ipairs(eq1) do
    local match = false
    for i2,v2 in ipairs(eq2) do
        if v1==v2 then 
            match=true 
            table.remove(eq2,i2)
            break
        end
    end
    assert(match,"No pair: "..v1)
end

-- Assert that every data in eq2 can be found in eq1
local eq1 = split(s1,"\n")
local eq2 = split(s2,"\n")
for i2,v2 in ipairs(eq2) do
    local match = false
    for i1,v1 in ipairs(eq1) do
        if v1==v2 then 
            match=true 
            table.remove(eq1,i1)
            break
        end
    end
    assert(match,"No pair: "..v2)
end

local test = ton.read("test.ton")

--             same as ["Animal"]["Ground"]                                            evry data is represented as a table
test["Creature"].Animal.Ground["Mammal"]["Anthropoid"].Human.Male["Albert Einstein"]={["Description"]={["German physicist"]={}},["Lived"]={[1879]={},[1955]={}}}

print(table.toString(test))
