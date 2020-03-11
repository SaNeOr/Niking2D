#pragma once

#include "Niking2D.h"

#include "Level.h"

class GameLayer : public Niking2D::Layer {
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Niking2D::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Niking2D::Event& event) override;

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	Niking2D::Scope<Niking2D::OrthographicCamera> m_Camera;

	Level m_Level;
	float m_Time = 0.0f;
	
	enum class GameState {
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;


};