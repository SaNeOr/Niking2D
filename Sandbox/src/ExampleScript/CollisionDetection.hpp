#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class CollisionDetection {
public:
	static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
	{
		float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
		float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

		if ((s < 0) != (t < 0))
			return false;

		float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

		return A < 0 ?
			(s <= 0 && s + t >= A) :
			(s >= 0 && s + t <= A);
	}

	static bool CollisionTest(float aPosX, float aPosY, float aRotation, float bPosX, float bPosY, float bScaleX, float bScaleY, float bRotation)
	{

		if (glm::abs(aPosY) > 8.5f)
			return true;

		glm::vec4 playerVertices[4] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};

		//const auto& pos = m_Player.GetPosition();
		glm::vec2& pos = glm::vec2{ aPosX, aPosY };
		glm::vec4 playerTransformedVerts[4];
		for (int i = 0; i < 4; i++)
		{
			playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(aRotation), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
				* playerVertices[i];
		}

		// To match Triangle.png (each corner is 10% from the texture edge)
		glm::vec4 pillarVertices[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		
		glm::vec2 tri[3];

		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { bPosX, bPosY, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(bRotation), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { bScaleX, bScaleY, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}
		return false;
	}

};