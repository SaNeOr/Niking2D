#include "ScriptGameLayer.h"
#include "ParticleSystem.h"
#include "CollisionDetection.hpp"

using namespace Niking2D;
#include "sol.hpp"

ScriptGameLayer::ScriptGameLayer()
	:Layer("ScriptGameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
	N2_CLIENT_ERROR(window.GetWidth());

	sol::usertype<ParticleSystem> particleSystem =
		Script::GetLuaState()->new_usertype<ParticleSystem>("ParticleSystem", sol::constructors<ParticleSystem()>());	
	
	particleSystem["Emit"] = &ParticleSystem::Emit;
	particleSystem["OnUpdate"] = &ParticleSystem::OnUpdate;
	particleSystem["OnRender"] = &ParticleSystem::OnRender;

	sol::usertype<ParticleProps> particleProps =
		Script::GetLuaState()->new_usertype<ParticleProps>("ParticleProps", sol::constructors<ParticleProps()>());
	particleProps["Rotated"] = &ParticleProps::Rotated;
	particleProps["rotatedX"] = &ParticleProps::RotatedX;
	particleProps["rotatedY"] = &ParticleProps::RotatedY;
	particleProps["SetPosition"] = &ParticleProps::SetPosition;
	particleProps["SetVelocity"] = &ParticleProps::SetVelocity;

	Script::GetLuaState()->set_function("IsCollision", sol::resolve<bool(float aPosX, float aPosY, float aRotation, float bPosX, float bPosY, float bScaleX, float bScaleY, float bRotation)>(&CollisionDetection::CollisionTest));

	Script::GetLuaState()->set_function("SetCameraPosition", sol::resolve<void(float, float)>(&ScriptGameLayer::SetCameraPosition), this);
	Script::GetLuaState()->set_function("DrawFont", sol::resolve<void(std::string content, float posX, float posY, float size)>(&ScriptGameLayer::DrawFont), this);

	Script::GetLuaState()->set("Width", Application::Get().GetWindow().GetWidth());
	Script::GetLuaState()->set("Height", Application::Get().GetWindow().GetHeight());
	N2_CLIENT_ERROR(Application::Get().GetWindow().GetWidth());

	//int i = (*Script::GetLuaState())["Height"];
	//N2_CLIENT_ERROR(i);
	
	Script::GetLuaState()->script_file("src/ExampleScript/main.lua");
}
 


void ScriptGameLayer::OnAttach()
{
	Script::GetLuaState()->script("Init()");


	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
}

void ScriptGameLayer::OnDetach()
{
}

void ScriptGameLayer::OnUpdate(Niking2D::Timestep ts)
{

	// Update
	float dt = ts;
	(*Script::GetLuaState())["Update"](dt);
	//(*lua)["Update"](ts);

	// Render
	RenderCommand::SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	RenderCommand::Clear();

	Renderer2D::BeginScene(*m_Camera);
	Script::GetLuaState()->script("Draw()");
	Renderer2D::EndScene();
}

void ScriptGameLayer::OnImGuiRender()
{
	Script::GetLuaState()->script("DrawUI()");

	//auto pos = ImGui::GetWindowPos();
	//auto width = Application::Get().GetWindow().GetWidth();
	//auto height = Application::Get().GetWindow().GetHeight();
	//pos.x += width * 0.5f - 300.0f;
	//pos.y += 50.0f;
	//ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
}

void ScriptGameLayer::OnEvent(Niking2D::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(N2_BIND_EVENT_FN(ScriptGameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(N2_BIND_EVENT_FN(ScriptGameLayer::OnMouseButtonPressed));
}

bool ScriptGameLayer::OnWindowResize(Niking2D::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

bool ScriptGameLayer::OnMouseButtonPressed(Niking2D::MouseButtonPressedEvent& e)
{
	Script::GetLuaState()->script("OnMouseButtonPressed()");
	return false;
}

void ScriptGameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camSize = 8.0f;
	float bottom = -camSize;
	float top = camSize;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}

void ScriptGameLayer::SetCameraPosition(float x, float y)
{
	m_Camera->SetPosition(glm::vec3(x, y, 0.0f));
}

void ScriptGameLayer::DrawFont(std::string content, float posX, float posY, float size)
{
	auto pos = ImGui::GetWindowPos();
	pos.x += posX; pos.y += posY;

	ImGui::GetForegroundDrawList()->AddText(m_Font, size, pos, 0xffffffff, content.c_str());
}
