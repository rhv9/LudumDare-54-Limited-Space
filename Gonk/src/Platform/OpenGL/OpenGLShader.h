#pragma once

#include "Gonk/Renderer/Shader.h"

// TODO: Remove!
typedef unsigned int GLenum;

namespace Gonk {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UniformInt(const std::string& name, const int val) const;

		void UniformFloat(const std::string& name, const float val) const;
		void UniformFloat2(const std::string& name, const glm::vec2& vector) const;
		void UniformFloat3(const std::string& name, const glm::vec3& vector) const;
		void UniformFloat4(const std::string& name, const glm::vec4& vector) const;

		void UniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UniformMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
	};

}