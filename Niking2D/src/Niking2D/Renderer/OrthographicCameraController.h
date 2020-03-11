#pragma once

#include "Niking2D/Renderer/OrthographicCamera.h"
#include "Niking2D/Core/Timestep.h"
#include "Niking2D/Events/MouseEvent.h"
#include "Niking2D/Events/ApplicationEvent.h"
namespace Niking2D {
	class OrthographicCameraController {

	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		
		void OnUpdate(Timestep ts);

		OrthographicCamera& GetCamera() { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRation;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f,0.0f };
		float m_CameraRotation = 0.0f;	//	In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;


	};



}