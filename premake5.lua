workspace "Gonk"
	architecture "x86_64"
	startproject "LudumDare54"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Gonk/vendor/GLFW/include"
IncludeDir["Glad"] = "Gonk/vendor/Glad/include"
IncludeDir["ImGui"] = "Gonk/vendor/imgui"
IncludeDir["glm"] = "Gonk/vendor/glm"
IncludeDir["stb_image"] = "Gonk/vendor/stb_image"
IncludeDir["entt"] = "Gonk/vendor/entt/include"

group "Dependencies"
	include "Gonk/vendor/GLFW"
	include "Gonk/vendor/Glad"
	include "Gonk/vendor/imgui"

group ""

project "Gonk"
	location "Gonk"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gkpch.h"
	pchsource "Gonk/src/gkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
			"GK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		optimize "on"
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Gonk/vendor/spdlog/include",
		"Gonk/src",
		"Gonk/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}
	
	links
	{
		"Gonk"
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		optimize "on"


project "Gonkit"
	location "Gonkit"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Gonk/vendor/spdlog/include",
		"Gonk/src",
		"Gonk/vendor",
		"%{IncludeDir.glm}",
		 "%{IncludeDir.entt}",
	}
	
	links
	{
		"Gonk"
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		optimize "on"





project "LudumDare54"
	location "LudumDare54"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"Gonk/vendor/spdlog/include",
		"Gonk/src",
		"Gonk/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}
	
	links
	{
		"Gonk"
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		optimize "on"