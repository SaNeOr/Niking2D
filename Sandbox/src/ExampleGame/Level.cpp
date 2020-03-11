#include "Level.h"

using namespace Niking2D;
void Level::Init()
{
	m_TriangleTexture = Texture2D::Create("assets/textures/Triangle.png");

	m_Player.LoadAssets();

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}

void Level::OnUpdate(Niking2D::Timestep ts)
{
	m_Player.OnUpdate(ts);

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		m_PillarTarget += 10.0f;
	}

}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	glm::vec4 color = glm::vec4(1.0f);
	//	Background
	Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	// Floor and ceiling
	Renderer2D::DrawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
	Renderer2D::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);

	for (auto& pillar : m_Pillars)
	{
		Renderer2D::DrawQuad(pillar.TopPosition, pillar.TopScale, glm::radians(180.0f), m_TriangleTexture, 1.0f, color);
		Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, 0.0f, m_TriangleTexture, 1.0f, color);
	}



	m_Player.OnRender();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.z = index * 0.1f - 0.5f + 0.05f;

	float center = Random::Float() * 35.0f - 17.5f;
	float gap = 2.0f + Random::Float() * 5.0f;

	pillar.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;


}
