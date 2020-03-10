#include "n2pch.h"
#include "OrthographicCameraController.h"
#include "Niking2D/Core/Input.h"
#include "Niking2D/Core/KeyCodes.h"

Niking2D::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
	:m_AspectRation(aspectRatio),
	m_Camera(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), 
	m_Rotation (rotation){}

void Niking2D::OrthographicCameraController::OnUpdate(Timestep ts)
{
	N2_PROFILE_FUNCTION();

	//	Forward Move
	if (Input::IsKeyPressed(N2_KEY_A)) {

		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;

	}
	if (Input::IsKeyPressed(N2_KEY_D)) {
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	if (Input::IsKeyPressed(N2_KEY_W)) {
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation + 90.0f)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation + 90.0f)) * m_CameraTranslationSpeed * ts;
	}
	if (Input::IsKeyPressed(N2_KEY_S)) {
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation + 90.0f) ) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation + 90.0f) ) * m_CameraTranslationSpeed * ts;
	}

	if (m_Rotation) {


		if (Input::IsKeyPressed(N2_KEY_Q)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Input::IsKeyPressed(N2_KEY_E)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;
		m_Camera.SetRotation(m_CameraRotation);
	}
	m_Camera.SetPosition(m_CameraPosition);
	m_CameraTranslationSpeed = m_ZoomLevel;

}

void Niking2D::OrthographicCameraController::OnEvent(Event & e)
{
	N2_PROFILE_FUNCTION();

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(N2_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(N2_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

}

bool Niking2D::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
{

	m_ZoomLevel -= e.GetYOffset() * .25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

	return false;
}

bool Niking2D::OrthographicCameraController::OnWindowResized(WindowResizeEvent & e)
{
	m_AspectRation = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}


