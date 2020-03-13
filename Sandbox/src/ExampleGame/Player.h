#pragma once

#include<Niking2D.h>
#include "ParticleSystem.h"

#include "Random.h"
class Player {
public:
	Player();

	void LoadAssets();

	void OnUpdate(Niking2D::Timestep ts);
	void OnRender();

	const glm::vec2 GetPosition()const { return m_Position; }
	float GetRotation() { return m_Velocity.y * 4.0f - 90.0f; }

	void OnImGuiRender();

	//void Reset();
private:
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	float m_EnginePower = 0.5f;
	float m_Gravity = 0.4f;

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Niking2D::Ref<Niking2D::Texture2D> m_ShipTexture;
};