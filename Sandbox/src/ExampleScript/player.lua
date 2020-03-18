player ={}
player.sprite = sprites.player

player.position = {}
player.position.x = -10.0;
player.position.y = 0.0;

player.velocity = {}
player.velocity.x = 5.0;
player.velocity.y = 0.0;

player.gravity = 0.4
player.enginePower = 0.5


player.particleSystem = ParticleSystem.new()
player.engineParticle = ParticleProps.new()

function player:Update(dt)
    if IsKeyPressed('space') then
        player.velocity.y = player.velocity.y + player.enginePower
        
        ---------------------------------------------------------------
        ----------------- Particle Setting-----------------------------
        local emissionPoint = {x = 0.0, y = -0.6}
        local rotation = math.rad(player:GetRotation())
        player.engineParticle:Rotated(rotation,emissionPoint.x, emissionPoint.y )
        player.engineParticle:SetPosition(player:GetPosition().x + player.engineParticle.rotatedX, player:GetPosition().y + player.engineParticle.rotatedY)
        player.engineParticle:SetVelocity(-2.0, -player.velocity.y * 0.2 - 0.2)

        player.particleSystem:Emit(player.engineParticle)
        ----------------------------------------------------------------
        ----------------------------------------------------------------

	else
		player.velocity.y = player.velocity.y - player.gravity
	end

	if player.velocity.y > 20.0 then
		player.velocity.y = 20.0
	elseif player.velocity.y < -20.0 then
		player.velocity.y = -20.0
	end

	player.position.x = player.position.x + player.velocity.x  * dt
    player.position.y = player.position.y + player.velocity.y  * dt
    
    player.particleSystem:OnUpdate(dt)

end

function player:Draw( )
    DrawQuadRTex(sprites.player, player.position.x, player.position.y, 1.0, 1.3, math.rad(player:GetRotation()))
    player.particleSystem:OnRender()
end

function player:GetRotation()
	return player.velocity.y * 4.0 - 90
end

function player:GetPosition()
	return player.position
end

function player:GetScore()
    return (player.position.x + 10.0) / 10.0
end

function player:Reset()
    player.position.x = -10.0;
    player.position.y = 0.0;

    player.velocity.x = 5.0;
    player.velocity.y = 0.0;
end