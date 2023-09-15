#pragma once

namespace Gonk {

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string GetName() const = 0;

		virtual void SetMat4(const std::string& name, const glm::mat4 matrix) = 0;
		virtual void SetInt(const std::string& name, const int val) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& val) = 0;

		static Ref<Shader> Create(const std::string&name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& path);

	};

	class ShaderLibrary
	{
	public:

		void Add(const std::string& name, Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& path);
		Ref<Shader> Load(const std::string& name, const std::string& path);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}