#include "Player.h"
#include "imgui.h"

#include<glm/gtc/matrix_transform.hpp>

using namespace Niking2D;

Player::Player()
{
}

void Player::LoadAssets()
{
	m_ShipTexture = Texture2D::Create("assets/textures/Ship.png");
}

void Player::OnUpdate(Niking2D::Timestep ts)
{
	if (Input::IsKeyPressed(N2_KEY_SPACE)) {
		m_Velocity.y += m_EnginePower;
	}
	else {
		m_Velocity.y -= m_Gravity;
	}

	m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
	m_Position += m_Velocity * (float)ts;
}

void Player::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, { 1.0f, 1.3f }, glm::radians(GetRotation()), m_ShipTexture);
}

void Player::OnImGuiRender()
{
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);

	//ImGui::Text("m_EnginePower	: %lf",	m_EnginePower);
	ImGui::Text("m_Velocity.y		: %lf", m_Velocity.y);
}
