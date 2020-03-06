#include <Niking2D.h>



class ExampleLayer :public Niking2D::Layer {
public:
	ExampleLayer();


	virtual void OnAttach();
	virtual void OnDetach();


	void OnUpdate(Niking2D::Timestep ts) override;

	virtual void OnImGuiRender() override;


	void OnEvent(Niking2D::Event& event) override;

	bool OnKeyPressedEvent(Niking2D::KeyPressedEvent& event) {
		//if (event.GetKeyCode() == N2_KEY_LEFT) {
		//	m_CameraPosition.x -= m_CameraMoveSpeed;

		//}	
		//if (event.GetKeyCode() == N2_KEY_RIGHT) {
		//	m_CameraPosition.x += m_CameraMoveSpeed;

		//}		
		//if (event.GetKeyCode() == N2_KEY_DOWN) {
		//	m_CameraPosition.y -= m_CameraMoveSpeed;

		//}	
		//if (event.GetKeyCode() == N2_KEY_UP) {
		//	m_CameraPosition.y += m_CameraMoveSpeed;

		//}

		return false;

	}

private:
	Niking2D::ShaderLibrary m_ShaderLibrary;
	Niking2D::Ref<Niking2D::Shader> m_Shader;



	Niking2D::Ref<Niking2D::VertexArray> m_VertexArray;
	Niking2D::Ref<Niking2D::Shader> m_FlatColorShader, m_TextureShader;
	Niking2D::Ref<Niking2D::VertexArray> m_SquareVA;

	Niking2D::Ref<Niking2D::Texture2D> m_Texture, m_testTexture;

	//Niking2D::OrthograhicCamera m_Camera;
	Niking2D::OrthographicCameraController m_Camera;


	//glm::vec3 m_CameraPosition;
	//float m_CameraRotation = 0.0f;
	//float m_CameraMoveSpeed = 5.0f;
	//float m_CameraRotationSpeed = 100.0f;


	glm::vec3 m_SquarePosition;

	float m_SquareMoveSpeed = 1.0f;



	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

