workspace "Alpha 9"
  filename "Alpha-9"
  architecture "x64"
  startproject "Sandbox"
  configurations { "Debug", "Release" }

project "Alpha-9"
  location "Alpha-9"
  kind "SharedLib"
  language "C++"

  filter "system:Windows"
    defines "A9_PLATFORM_WINDOWS"

  filter "system:Mac"
    defines "A9_PLATFORM_MAC"

  filter "system:Linux"
    defines "A9_PLATFORM_LINUX"



  filter "configurations:Debug"
        defines "A9_DEBUG"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
  filter "configurations:Release"
      runtime "Release"
      optimize "On"
