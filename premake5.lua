workspace "Alpha 9"
	architecture "x64"
	filename "Alpha-9"
	startproject "Sandbox"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

include "Alpha-9/third-party/GLFW"
include "Alpha-9/third-party/Glad"

project "Alpha-9"
	location "Alpha-9"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/Alpha-9")
	objdir ("bin/int/" .. outputdir .. "/Alpha-9")

	pchheader "a9pch.hpp"
	pchsource "a9pch.cpp"

	files
	{
		"%{prj.name}/core/Alpha-9",
		"%{prj.name}/core/**.h*",
		"%{prj.name}/core/**.c*",
		"%{prj.name}/platform/**.h*",
		"%{prj.name}/platform/**.c*",
		"%{prj.name}/third-party/glm/glm/**.hpp",
		"%{prj.name}/third-party/glm/glm/**.inl"
	}
	includedirs
	{
		"%{prj.name}/core",
		"%{prj.name}/platform",
		"%{prj.name}/third-party/GLFW/include",
		"%{prj.name}/third-party/Glad/include",
		"%{prj.name}/third-party/glm/glm",
		"%{prj.name}/third-party/spdlog/include"
	}
	links
	{
		"GLFW",
		"GLAD"
	}

	filter "system:Windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"A9_PLATFORM_WINDOWS",
			"A9_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		links { "opengl32.lib" }
		postbuildcommands
		{
			-- Copying the (Dynamic) Linked Library into the folder with the executable
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
	filter "system:Mac"
		defines "A9_PLATFORM_MAC"
	filter "system:Linux"
		defines "A9_PLATFORM_LINUX"



	filter "configurations:Debug"
		defines "A9_DEBUG_MODE"
		runtime "Debug"
		symbols "On"
		optimize "Debug"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h*",
		"%{prj.name}/src/**.c*"
	}
	includedirs
	{
		"%{prj.name}/src",
		"Alpha-9/core",
		"Alpha-9/platform",
		"Alpha-9/third-party/Glad/include",
		"Alpha-9/third-party/spdlog/include"
	}
	links
	{
		"Alpha-9"
	}


	filter "system:Windows"
		cppdialect "C++17"
		systemversion "latest"
		defines "A9_PLATFORM_WINDOWS"
	filter "system:Mac"
		defines "A9_PLATFORM_MAC"

	filter "system:Linux"
		defines "A9_PLATFORM_LINUX"



	filter "configurations:Debug"
		defines "A9_DEBUG_MODE"
		runtime "Debug"
		symbols "On"
		optimize "Debug"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"