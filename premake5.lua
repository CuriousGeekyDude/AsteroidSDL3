workspace "AsteroidSDL3"
	configurations{"Debug", "Release"}
	platforms{"x64"}

project "AsteroidSDL3"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"


	vpaths {
		["deps/**"] = {"dependencies/**.h", "dependencies/**.hpp", "dependencies/**.c", "dependencies/**.cpp"},
        ["src/**"] = { "src/**.cpp" },
        ["include/**"] = { "include/**.h", "include/**.hpp" },
    }

	files{"include/**.hpp", 
		  "include/**.h",
		  "src/**.c",
		  "src/**.cpp",
		  "dependencies/SDL3/include/**.hpp",
		  "dependencies/SDL3/include/**.h",
		  "dependencies/imgui/**.hpp",
		  "dependencies/imgui/**.c",
		  "dependencies/imgui/**.cpp",
		  "dependencies/imgui/**.h",
		  "dependencies/glm/**.h",
		  "dependencies/glm/**.hpp",
		  "dependencies/SDL3_image/**.hpp",
		  "dependencies/SDL3_image/**.h"}
		  
	targetdir "x64/%{cfg.buildcfg}"
	objdir ("bin-intermediate/%{cfg.buildcfg}")
	includedirs{"include/",
				"dependencies/SDL3/include/",
				"dependencies/imgui/",
				"dependencies/glm/",
				"dependencies/SDL3_image/include/"}
	libdirs{"dependencies/SDL3/lib/64build/",
			"dependencies/SDL3_image/lib/64build/"}
	links{"SDL3", "SDL3_image"}
	
	postbuildcommands {
        "{COPY} dependencies/SDL3/lib/64build/SDL3.dll x64/%{cfg.buildcfg}",
		"{COPY} dependencies/SDL3_image/lib/64build/SDL3_image.dll x64/%{cfg.buildcfg}"
    }

	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

	filter "toolset:gcc or toolset:clang"
		buildoptions { "-Wall", "-Wextra", "-Werror" }

	filter "toolset:msc"
		buildoptions { "/W4 /WX" }

	