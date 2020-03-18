#pragma once

#include "Niking2D/Core/Core.h"

#include "Niking2D/Renderer/Renderer2D.h"
#include "Niking2D/Renderer/Texture.h"
#include "Niking2D/Core/Input.h"

#include "sol.hpp"

namespace Niking2D {
	class Script {
	public:
		static void Init();

		inline static std::shared_ptr<sol::state>& GetLuaState() {
			return s_LuaState;
		}

	private:
		static void BindInitFunction();
		
		static void BindUpdateFunction();

		static void BindDrawFunction();


	private:
		//====================	Adapter============================================

		//	======Init Function=========================
		static Ref<Niking2D::Texture2D> LoadTexture(std::string path);
		//	============================================


		//	======Update Function=========================
		static bool IsKeyPressed(std::string);

		//	============================================


		//	======Draw Function=========================
		static void DrawQuad(float x, float y, float width, float height, float r, float g, float b, float a);
		static void DrawQuad(float x, float y, float z, float width, float height, float r, float g, float b, float a);

		static void DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float width, float height);
		static void DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float width, float height, float rotation);
		static void DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float z, float width, float height, float rotation);
		//static void DrawQuadTex(float x, float y, float width, float height, const Ref<Texture2D>& texture,  float r, float g, float b, float a);
		//	============================================


	

	private:
		static std::shared_ptr<sol::state> s_LuaState;
	};
}