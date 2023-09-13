#include "gkpch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

static GLenum ShaderTypeFromString(std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	else if (type == "fragment")
		return GL_FRAGMENT_SHADER;

	return 0;
}

namespace Gonk {
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		GK_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(ReadFile(path));
		Compile(shaderSources);

		// extract name from file path
		size_t lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		// TODO: Potential errors, but this works so who cares!
		size_t dot = path.rfind(".");
		size_t count = dot == std::string::npos ? path.size() - lastSlash : dot - lastSlash;
		m_Name = path.substr(lastSlash, count);

	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GK_PROFILE_FUNCTION();

		m_Name = name;
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}
	OpenGLShader::~OpenGLShader()
	{
		GK_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		GK_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		GK_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetMat4(const std::string& name, glm::mat4 matrix)
	{
		GK_PROFILE_FUNCTION();

		UniformMat4(name, matrix);
	}

	void OpenGLShader::SetInt(const std::string& name, const int val)
	{
		GK_PROFILE_FUNCTION();

		UniformInt(name, val);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& val)
	{
		GK_PROFILE_FUNCTION();

		UniformFloat4(name, val);
	}

	void OpenGLShader::UniformInt(const std::string& name, const int val) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(loc, val);
	}

	void OpenGLShader::UniformFloat(const std::string& name, const float val) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(loc, val);
	}

	void OpenGLShader::UniformFloat2(const std::string& name, const glm::vec2& vector) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(loc, vector.x, vector.y);
	}

	void OpenGLShader::UniformFloat3(const std::string& name, const glm::vec3& vector) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(loc, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UniformFloat4(const std::string& name, const glm::vec4& vector) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::UniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		int loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			GK_CORE_ERROR("Could not open file {0}", path);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		GK_CORE_ASSERT(pos != std::string::npos, "No declaration of type of shader found!");

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			GK_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			GK_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax Error!");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		int shaderIndex = 0;
		GLuint shaderIDs[2];

		GK_CORE_ASSERT(shaderSources.size() <= 2, "Only supports up to 2 shaders.");

		for (auto&& [type, source] : shaderSources)
		{
			// Create an empty <type> shader handle
			GLuint shader = glCreateShader(type);

			const char* sourceCharPtr = source.c_str();
			glShaderSource(shader, 1, &sourceCharPtr, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				GK_CORE_ERROR("Shader compilation failure!");
				GK_CORE_ASSERT(false, infoLog.data());
				return;
			}

			// Add the shader id.
			shaderIDs[shaderIndex++] = shader;
		}

		m_RendererID = glCreateProgram();  

		// Attach our shaders to our program
		for (auto shader : shaderIDs)
		{
			glAttachShader(m_RendererID, shader);
		}

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.

			for (auto shader : shaderIDs)
			{
				glDeleteShader(shader);
			}

			GK_CORE_ERROR("Program Link failure!");
			GK_CORE_ASSERT(false, infoLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		for (auto shader : shaderIDs)
		{
			glDetachShader(m_RendererID, shader);
			glDeleteShader(m_RendererID);
		}

	}


}