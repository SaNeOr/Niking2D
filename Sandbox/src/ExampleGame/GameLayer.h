#pragma once

#include "Niking2D.h"

#include "Level.h"
#include <imgui.h>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"


class GameLayer : public Niking2D::Layer {
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Niking2D::Timestep ts) override;

	virtual void OnImGuiRender() override;

	void OnEvent(Niking2D::Event& e) override;
	bool OnMouseButtonPressed(Niking2D::MouseButtonPressedEvent& e);
	bool OnWindowResize(Niking2D::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

	void LevelUpdate(Niking2D::Timestep ts);

private:
	Niking2D::Scope<Niking2D::OrthographicCamera> m_Camera;

	Level m_Level;
	ImFont* m_Font;

	float m_Time = 0.0f;
	bool m_Blink = false;
	
	enum class GameState {
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;

	sol::state* m_LuaState;

};