#include "chpch.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

namespace Crutch
{

	void CShader::Bind()
	{
		glUseProgram( m_shaderId );
	}

	void CShader::Unbind()
	{

	}

	bool CShader::Load( const std::string& path )
	{
		glLinkProgram(m_shaderId, 1, "SOURCE", 0);
	}

}