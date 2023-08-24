workspace "Gonk"
	architecture "x64"
	startproject "Sandbox"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Gonk/vendor/GLFW/include"
IncludeDir["Glad"] = "Gonk/vendor/Glad/include"
IncludeDir["ImGui"] = "Gonk/vendor/imgui"

group "Dependencies"
	include "Gonk/vendor/GLFW"
	include "Gonk/vendor/Glad"
	include "Gonk/vendor/imgui"

group ""

project "Gonk"
	location "Gonk"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gkpch.h"
	pchsource "Gonk/src/gkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
			"GK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"" )
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		symbols "On"
		optimize "On"
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Gonk/src"
	}
	
	links
	{
		"Gonk"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GK_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GK_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "GK_DIST"
		runtime "Release"
		symbols "On"