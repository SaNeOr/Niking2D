#pragma once

#include <string>
#include "Niking2D/Core/Core.h"

namespace Niking2D {
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind()const = 0;

		virtual void SetData(void* data, unsigned int size) = 0;

		virtual int GetWidth() const = 0;
		 virtual int GetHeight() const = 0;

	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);

	};
}