#pragma once

#include <Niking2D.h>
#include "glm/gtc/matrix_transform.hpp"

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;

	float RotatedX, RotatedY;

	ParticleProps() {
		Position = { 0.0f, 0.0f };
		Velocity = { -2.0f, 0.0f }, VelocityVariation = { 3.0f, 1.0f };
		SizeBegin = 0.5f, SizeEnd = 0.0f, SizeVariation = 0.3f;
		ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
		LifeTime = 1.0f;
	}

	void Rotated(float rotation, float posX, float posY) {
		glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(posX, posY, 0.0f, 1.0f);
		RotatedX = rotated.x;
		RotatedY = rotated.y;
	}



	void SetPosition(float x, float y) { Position = { x,y }; }

	void SetVelocity(float velocityX, float velocityY){
		Velocity = { velocityX,velocityY };
	}
	
	void SetVelocityVariation(float variationX, float variationY) {
		VelocityVariation = { variationX, variationY };
	}

	void SetColorBegin(float r, float g, float b, float a) { ColorBegin = { r,g,b,a }; }
	void SetColorEnd(float r, float g, float b, float a) { ColorEnd = { r,g,b,a }; }

	void SetSizeBegin(float size) { SizeBegin = size; }
	void SetSizeEnd(float size) { SizeEnd = size; }
	void SetSizeVariation(float variation) { SizeVariation = variation; }
	void SetLifeTime(float time) { LifeTime = time; }
};

class ParticleSystem
{
public:
	ParticleSystem();
	
	void Emit(const ParticleProps& particleProps);

	void OnUpdate(float ts);
	void OnRender();

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
};