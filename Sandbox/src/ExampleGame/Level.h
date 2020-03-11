#pragma once

#include "Player.h"

struct Pillar
{
	glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
	glm::vec2 TopScale = { 15.0f, 20.0f };
	
	glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f };
	glm::vec2 BottomScale = { 15.0f, 20.0f };

};

class Level {
public:
	void Init();

	void OnUpdate(Niking2D::Timestep ts);
	void OnRender();

	Player& GetPlayer() { return m_Player; }
	void OnImGuiRender();
	
private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();

private:
	Player m_Player;

	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;

	std::vector<Pillar> m_Pillars;


	Niking2D::Ref<Niking2D::Texture2D> m_TriangleTexture;


};