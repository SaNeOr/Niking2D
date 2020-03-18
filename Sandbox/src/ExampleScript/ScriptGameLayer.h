#pragma once

#include "Niking2D.h"

#include <imgui.h>


#define SOL_ALL_SAFETIES_ON 1


class ScriptGameLayer : public Niking2D::Layer {
public:
	ScriptGameLayer();
	virtual ~ScriptGameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Niking2D::Timestep ts) override;

	virtual void OnImGuiRender() override;


	void OnEvent(Niking2D::Event& e) override;
	bool OnMouseButtonPressed(Niking2D::MouseButtonPressedEvent& e);
	bool OnWindowResize(Niking2D::WindowResizeEvent& e);



private:
	void CreateCamera(uint32_t width, uint32_t height);

// =======for script=============================================
private:
	void SetCameraPosition(float x, float y);
	void DrawFont(std::string content, float posX, float posY, float size);
	

private:
	Niking2D::Scope<Niking2D::OrthographicCamera> m_Camera;

	enum class GameState {
		Play = 0, MainMenu = 1, GameOver = 2
	};
	GameState m_State = GameState::MainMenu;

	ImFont* m_Font;

};