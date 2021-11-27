#pragma once


namespace Crutch
{
	enum class EShaderType
	{
		Vertex		= 0,
		Fragment,

		Unknown
	};

	class CShader
	{
	public:
		CShader() = default;

		void Bind();
		void Unbind();

		bool Load( const std::string& path );

	private:

		EShaderType m_type;
		unsigned int m_shaderId;
	};
}