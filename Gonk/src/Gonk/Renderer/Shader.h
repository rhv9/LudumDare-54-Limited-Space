#pragma once

namespace Gonk {

	class Shader
	{
	public:
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UniformMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		uint32_t m_RendererID;
	};

}