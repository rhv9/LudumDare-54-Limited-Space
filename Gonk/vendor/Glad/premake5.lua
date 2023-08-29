project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
	}

	includedirs
	{
		"include",
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