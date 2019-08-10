-- premake5.lua
workspace "Chlorophyll"
   configurations { "Debug", "Release" }

project "Chlorophyll"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   links{"SDL2","SDL2_ttf","SDL2_mixer","SDL2_image"}

   files { "**.h", "**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
