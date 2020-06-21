#include "Shader.h"
#include "GLErrorMessage.h"

#include <iostream>
#include <fstream>
#include<string>
#include <sstream>


Shader::Shader(const std::string &filepath)
	:m_FilePath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);

	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	
	
}

ShaderProgramSource Shader:: ParseShader(const std::string &filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	std::string line;
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				//set mode to vertex
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				//set mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(),ss[1].str() };

}

unsigned int Shader::ComplieShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Syntax Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" <<
			std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;

}

 unsigned int Shader:: CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = ComplieShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	return program;

}
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniformVec4f(const std::string &name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));

}

void Shader::SetUniformVec4f(const std::string &name, const glm::vec4 &vector)
{
	GLCall(glUniform4fv(GetUniformLocation(name),1,&vector[0]));

}

void Shader::SetUniform1f(const std::string &name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));

}
void Shader::SetUniform1i(const std::string &name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));

}

void Shader::SetUniformVec3f(const std::string &name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));

}

void Shader::SetUniformVec3f(const std::string &name, const glm::vec3 &vector)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1,&vector[0]));

}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1,GL_FALSE,&matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string &name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "warning:uniform '" << name << "' does not exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}