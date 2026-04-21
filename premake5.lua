workspace "Raycaster"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Raycaster"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "vendor/raylib/include"
    }

    filter "system:windows"
        libdirs { "vendor/raylib/lib/win" }
        links { "raylib", "opengl32", "gdi32", "winmm" }

    filter "system:linux"
        libdirs { "vendor/raylib/lib/linux" }
        links { "raylib", "GL", "m", "pthread", "dl", "rt", "X11" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
