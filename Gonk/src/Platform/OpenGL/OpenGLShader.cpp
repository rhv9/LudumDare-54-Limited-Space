#include "gkpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace Gonk {
	OpenGLShader::OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc)
	{

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			GK_CORE_ERROR("Vertex Shader compilation failure!");
			GK_CORE_ASSERT(false, infoLog.data());
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			GK_CORE_ERROR("Fragment Shader compilation failure!");
			GK_CORE_ASSERT(false, infoLog.data());
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GK_CORE_ERROR("Program Link failure!");
			GK_CORE_ASSERT(false, infoLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
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


}