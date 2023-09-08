#pragma once

namespace Gonk {

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);

	};

}