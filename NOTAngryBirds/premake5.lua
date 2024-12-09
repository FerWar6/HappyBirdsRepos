workspace "NOTAngryBirds"
    configurations { "Debug", "Release", "Dist" }
    architecture "x64"

project "NOTAngryBirds"
    kind "ConsoleApp"
    language "C++"
    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    targetdir("build/" .. OutputDir .. "/")
    objdir("build/Intermediates/" .. OutputDir .. "/")

    files {
        "source/**.h",
        "source/**.hpp",
        "source/**.c",
        "source/**.cpp"
    }

    includedirs {
        "Dependencies/SFML-2.6.1/include",
        "Dependencies/box2d-main/include",
        "Source"
    }

    libdirs {
        "Dependencies/SFML-2.6.1/lib",
        "Dependencies/box2d-main/lib"
    }

    links {
        "opengl32.lib",
        "freetype.lib", 
        "winmm.lib", 
        "gdi32.lib",
        "openal32.lib",
        "flac.lib",
        "vorbisenc.lib",
        "vorbisfile.lib",
        "vorbis.lib",
        "ogg.lib",
        "ws2_32.lib",
        "box2d.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    defines { "GAME_PLATFORM_WINDOWS", "SFML_STATIC" }

    filter "configurations:Debug"
        defines { "DEBUG", "ST_PLATFORM_WINDOWS" }
        runtime "Debug"
        symbols "On"
        links { 
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-network-s-d.lib",
            "sfml-system-s-d.lib",
            "sfml-window-s-d.lib" 
        }

    filter "configurations:Release"
        defines { "RELEASE", "ST_PLATFORM_WINDOWS" }
        runtime "Release"
        optimize "On"
        symbols "On"
        links { 
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib" 
        }

    filter "configurations:Dist"
        defines { "DIST", "ST_PLATFORM_WINDOWS" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        links { 
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib" 
        }
