level = {}
level.pillarTarget = 30.0
level.pillarIndex = 0

pillar = {}
pillar.sprite = sprites.triangle
pillar.topposition = {x = 0.0, y= 10.0, z= 0.0}
pillar.topscale = {x = 15.0, y = 20.0}

pillar.bottomposition = {x = 10.0, y= 10.0, z= 0.0}
pillar.bottomscale = { x = 15.0, y = 20.0}



pillars = {}

function level:Init()
    for i=1,5 do
        pillars[i] = {topposition = {}, bottomposition = {},bottomscale = {x = 15.0, y = 20.0}, topscale = {x = 15.0, y = 20.0} }
        CreatePillar(pillars[i], i, (i-1) * 10.0);

        print(player.position.x, player.position.y,player:GetRotation(),
        pillars[i].topposition.x, pillars[i].topposition.y,
        pillars[i].topscale.x, pillars[i].topscale.y)
    end
end

function level:Update()
    if player.position.x > level.pillarTarget then
        CreatePillar(pillars[level.pillarIndex + 1],level.pillarIndex, level.pillarTarget + 20.0)
        level.pillarIndex = (level.pillarIndex + 1) % 5
        level.pillarTarget = level.pillarTarget + 10.0 
    end

    for i=1,5 do
        if IsCollision(player.position.x, player.position.y,player:GetRotation(),
        pillars[i].topposition.x, pillars[i].topposition.y,
        pillars[i].topscale.x, pillars[i].topscale.y, 180.0) == true 
        or 
            IsCollision(player.position.x, player.position.y,player:GetRotation(),
            pillars[i].bottomposition.x, pillars[i].bottomposition.y,
            pillars[i].bottomscale.x, pillars[i].bottomscale.y, 0.0) == true
        then
            level:GameOver()
            return
        end
    end
end

function level:GameOver()
    GameState.State = GameState.GameOver
end

function level:Draw()
    local color = {r = 1.0, g = 1.0, b = 1.0, a = 1.0}
	-- Background
	DrawQuadZ(player.position.x, 0.0, -0.8, 50.0, 50.0, 0.3,0.3,0.3, 1.0)
	-- Floor and ceiling
	DrawQuad(player.position.x, 34.0, 50.0, 50.0, color.r, color.g, color.b, color.a)
    DrawQuad(player.position.x, -34.0, 50.0, 50.0, color.r, color.g, color.b, color.a)
    
    for i=1,5 do
        -- DrawQuadRTex(sprites.player, player.position.x, player.position.y, 1.0, 1.3, math.rad(GetRotation()))
        DrawQuadZRTex(pillar.sprite, pillars[i].topposition.x, pillars[i].topposition.y, pillars[i].topposition.z, pillars[i].topscale.x,  pillars[i].topscale.y, math.rad(180.0))

        DrawQuadZRTex(pillar.sprite, pillars[i].bottomposition.x,pillars[i].bottomposition.y, pillars[i].bottomposition.z, pillars[i].bottomscale.x,  pillars[i].bottomscale.y, 0)
    end
end

function CreatePillar(p, index, offset)
    local pillar = p
    pillar.topposition.x = offset
	pillar.bottomposition.x = offset
	pillar.topposition.z = (index-1) * 0.1 - 0.5
	pillar.bottomposition.z = (index-1) * 0.1 - 0.5 + 0.05

	local center = math.random(100) / 100 * 35.0 - 17.5
    local gap = 2.0 + math.random(100) / 100 * 5.0

	pillar.topposition.y = 10.0 - ((10.0 - center) * 0.2) + gap * 0.5
	pillar.bottomposition.y = -10.0 - ((-10.0 - center) * 0.2) - gap * 0.5
end