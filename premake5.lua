workspace "Alpha9"
	startproject "Test"

	architecture "x64"
	configurations 
	{ 
		"Debug", 
		"Release" 
	}

outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

include "Alpha9/third-party/GLFW"
include "Alpha9/third-party/Glad"

project "Alpha9"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	pchheader "a9pch.hpp"
	pchsource("%{prj.name}/core/a9pch.cpp")

	location "Alpha9"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/core/**.hpp",
		"%{prj.name}/core/**.cpp",
		"%{prj.name}/platform/**.hpp",
		"%{prj.name}/platform/**.cpp",
		"%{prj.name}/main/**.hpp",
		"%{prj.name}/main/**.cpp",
		"%{prj.name}/main/Alpha9",
		"%{prj.name}/main/Alpha9.h",
		"%{prj.name}/core/key_codes.inl",
		"%{prj.name}/core/events/input_events.inl",
		"%{prj.name}/core/events/window_events.inl",
	}

	includedirs
	{
		"%{prj.name}/core",
		"%{prj.name}/main",
		"%{prj.name}/platform",
		"%{prj.name}/third-party/Glad/include",
		"%{prj.name}/third-party/spdlog/include",
		"%{prj.name}/third-party/GLFW/include",
		"%{prj.name}/third-party/glm/"
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Test/\"")
	}

	filter "system:windows"
		systemversion "latest"
		linkoptions "/NODEFAULTLIB:libcmt.lib"
		
		defines
		{
			"A9_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "A9_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "A9_RELEASE"
		runtime "Release"
		optimize "on"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Alpha9/core",
		"Alpha9/main",
		"Alpha9/platform",
		"Alpha9/third-party/Glad/include",
		"Alpha9/third-party/spdlog/include",
		"Alpha9/third-party/GLFW/include",
		"Alpha9/third-party/glm/"
	}

	links
	{
		"Alpha9"
	}

	filter "system:windows"
		systemversion "latest"
		linkoptions "/NODEFAULTLIB:libcmt.lib"
		 
		defines
		{
			"A9_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "A9_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "A9_RELEASE"
		runtime "Release"
		optimize "on"