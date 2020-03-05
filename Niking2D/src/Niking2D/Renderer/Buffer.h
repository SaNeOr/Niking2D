#pragma once

namespace Niking2D {

	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Niking2D::ShaderDataType::Float:		return 4;
		case Niking2D::ShaderDataType::Float2:		return 4 * 2;
		case Niking2D::ShaderDataType::Float3:		return 4 * 3;
		case Niking2D::ShaderDataType::Float4:		return 4 * 4;
		case Niking2D::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Niking2D::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case Niking2D::ShaderDataType::Int:			return 4;
		case Niking2D::ShaderDataType::Int2:		return 4 * 2;
		case Niking2D::ShaderDataType::Int3:		return 4 * 3;
		case Niking2D::ShaderDataType::Int4:		return 4 * 4;
		case Niking2D::ShaderDataType::Bool:		return 1;
		}

		N2_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
		return 0;

		
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool noramlized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(noramlized)
		{}

		unsigned int GetComponementCount() const {
			switch (Type)
			{
			case Niking2D::ShaderDataType::Float:		return 1;
			case Niking2D::ShaderDataType::Float2:		return 2;
			case Niking2D::ShaderDataType::Float3:		return 3;
			case Niking2D::ShaderDataType::Float4:		return 4;
			case Niking2D::ShaderDataType::Mat3:		return 3 * 3;
			case Niking2D::ShaderDataType::Mat4:		return 4 * 4;
			case Niking2D::ShaderDataType::Int:			return 1;
			case Niking2D::ShaderDataType::Int2:		return 2;
			case Niking2D::ShaderDataType::Int3:		return 3;
			case Niking2D::ShaderDataType::Int4:		return 4;
			case Niking2D::ShaderDataType::Bool:		return 1;
			}

			N2_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
			return 0;
		}

		unsigned int GetStride() const {
			return GetComponementCount() * Size;
		}

	};


	class BufferLayout {
	public:

		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) {
			
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int GetStride()const { return m_Stride; }


		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }		
		
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride() {

			//unsigned int offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements) {
				//element.Offset = offset;
				element.Offset = m_Stride;
				//offset += element.Size;
				m_Stride += element.Size;
			}

		}
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind()const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;

		virtual unsigned int GetCount()const = 0 ;

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int size);

	};

}