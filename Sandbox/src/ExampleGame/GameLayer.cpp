#include "GameLayer.h"
#include <imgui.h>



using namespace Niking2D;

GameLayer::GameLayer()
	:Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	m_LuaState = new sol::state();

	m_LuaState->open_libraries(sol::lib::base);

	
	//(*m_LuaState)["LevelUpdate"] = &GameLayer::LevelUpdate;
	m_LuaState->set_function("LevelUpdate", &GameLayer::LevelUpdate, this);
	m_LuaState->script_file("src/examplegame/test.lua");

}

void GameLayer::OnAttach()
{
	

	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Niking2D::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	switch (m_State)
	{
		case GameState::Play:
		{
			//m_Level.OnUpdate(ts);
			(*m_LuaState)["OnUpdate"](ts);
			break;
		}
	}



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

#ifdef DEBUG
	float test = 0.0f;
	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();
#endif // DEBUG

	switch (m_State)
	{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}

	}

}

void GameLayer::OnEvent(Niking2D::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(N2_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(N2_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Niking2D::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Niking2D::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
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

void GameLayer::LevelUpdate(Timestep ts)
{
	m_Level.OnUpdate(ts);

}
