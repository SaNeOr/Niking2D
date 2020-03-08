#pragma once
#include <Niking2D.h>

class Sandbox2D :public Niking2D::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Niking2D::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Niking2D::Event& event) override;

private:
	Niking2D::OrthographicCameraController m_CameraController;

	//	Temp
	Niking2D::Ref<Niking2D::VertexArray> m_SquareVA;
	Niking2D::Ref<Niking2D::Shader> m_FlatColorShader;
	Niking2D::Ref<Niking2D::Texture2D> m_Texture;
	



	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};