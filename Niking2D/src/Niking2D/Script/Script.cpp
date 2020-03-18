#include "n2pch.h"
#include "Script.h"

#include "Niking2D/Core/KeyCodes.h"

namespace Niking2D {

	std::shared_ptr<sol::state> Script::s_LuaState;

	void Script::Init() {
		s_LuaState = std::make_shared<sol::state>();
		s_LuaState->open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);
		
		
		BindInitFunction();
		BindUpdateFunction();
		BindDrawFunction();
	}

	void Script::BindInitFunction()
	{
		s_LuaState->set_function("LoadTexture", sol::resolve<Ref<Niking2D::Texture2D>(std::string path)>(&Script::LoadTexture));
	}

	void Script::BindUpdateFunction()
	{
		s_LuaState->set_function("IsKeyPressed", sol::resolve<bool(std::string key)>(&Script::IsKeyPressed));
	}

	void Script::BindDrawFunction()
	{
		s_LuaState->set_function("DrawQuad", sol::resolve<void(float x, float y, float width, float height, float r, float g, float b, float a)>(&Script::DrawQuad));
		s_LuaState->set_function("DrawQuadZ", sol::resolve<void(float x, float y, float z, float width, float height, float r, float g, float b, float a)>(&Script::DrawQuad));
		s_LuaState->set_function("DrawQuadTex", sol::resolve<void(const Ref<Texture2D>& texture, float x, float y, float width, float height)>(&Script::DrawQuadTex));
		s_LuaState->set_function("DrawQuadRTex", sol::resolve<void(const Ref<Texture2D> & texture, float x, float y, float width, float height,  float rotation)>(&Script::DrawQuadTex));
		s_LuaState->set_function("DrawQuadZRTex", sol::resolve<void(const Ref<Texture2D> & texture, float x, float y, float z, float width, float height,  float rotation)>(&Script::DrawQuadTex));
	}



	//	======Init Function=========================
	Ref<Niking2D::Texture2D> Script::LoadTexture(std::string path)
	{
		return Texture2D::Create(path);
	}
	//	============================================


	//	======Update Function=========================
	bool Script::IsKeyPressed(std::string key)
	{
		unsigned int keycode = 0;

		if (key == "space")	keycode = N2_KEY_SPACE;


		return Niking2D::Input::IsKeyPressed(keycode);
	}
	//	============================================


	//	======Draw Function=========================
	void Script::DrawQuad(float x, float y, float width, float height, float r, float g, float b, float a)
	{
		Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(width, height), glm::vec4(r, g, b, a));
	}

	void Script::DrawQuad(float x, float y, float z, float width, float height, float r, float g, float b, float a)
	{
		Renderer2D::DrawQuad(glm::vec3(x, y,z), glm::vec2(width, height), glm::vec4(r, g, b, a));
	}

	void Script::DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float width, float height)
	{
		Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(width, height), texture);
	}
	void Script::DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float width, float height,  float rotation)
	{
		Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(width, height), rotation,texture);
	}
	void Script::DrawQuadTex(const Ref<Texture2D>& texture, float x, float y, float z, float width, float height, float rotation)
	{
		Renderer2D::DrawQuad(glm::vec3(x, y, z), glm::vec2(width, height), rotation, texture);
	}
	//	============================================

	
	


	

}
