#include "GameLayer.h"
#include <imgui.h>
using namespace Niking2D;

GameLayer::GameLayer()
	:Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

}

void GameLayer::OnAttach()
{
	m_Level.Init();

	//	TODO: Init Font
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Niking2D::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	m_Level.OnUpdate(ts);


	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });


	// Render
	RenderCommand::SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	RenderCommand::Clear();

	Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	float test = 0.0f;
	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();
}

void GameLayer::OnEvent(Niking2D::Event& event)
{
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
	
}
