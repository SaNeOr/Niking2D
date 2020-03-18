pillar = {}

pillar.num = 5
pillar.topposition = {x = 0.0, y= 10.0, z= 0.0}

pillars = {}

for i=1,5 do
    -- pillars[i] = pillar
    local t = pillar
    pillars[i]=t
    pillars[i].num = i
    
end

local t = pillars[1]
-- t.num = 10

pillars[1].topposition.y = 10.0
pillars[2].topposition.y = 20.0


function Test()
    if 1 == 1 then
        print("!!!")
        -- return
    end

    if 2==2 then
        print("@@@@@@@@")
    end
end


-- print(pillars[1].num)
-- print(pillars[1].topposition.y)
-- print(pillars[1].num)
-- for i=1,5 do
--     print(i)
-- end
-- Test()
-- print(1,2,3)

if 1 ==2 or 1==1 then
    print("!!!"..5)
end
