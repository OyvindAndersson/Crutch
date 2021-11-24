
local ROOT = "../"
bin_dir = "Binaries"
obj_dir = "Binaries-Int"

----------------------------------
-- WORKSPACE
----------------------------------
workspace           "Crutch"
    architecture    "x86_64"
    startproject    "Sandbox"
    configurations  { "Debug", "Release" }
    platforms       { "x64" }
	location		( ROOT )
    flags           { "MultiProcessorCompile" }
	
----------------------------------
-- Assemble all vendor includes into a dict
----------------------------------
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Crutch/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Crutch/vendor/GLAD/include"
IncludeDir["glm"] = "%{wks.location}/Crutch/vendor/glm"

-- The general folder-name rule for projects (i.e: "Debug-Windows-x64")
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

----------------------------------
-- Include other vendor projects
----------------------------------
group "Thirdparty"
	include (ROOT .. "Crutch/vendor/GLFW")
	include (ROOT .. "Crutch/vendor/GLAD")
group ""

----------------------------------
-- Crutch Project
----------------------------------
project "Crutch"
    location  "%{wks.location}/Crutch"
	kind 	  "StaticLib"
	staticruntime "off"
    language  "C++"
    cppdialect "C++17"

    targetdir( "%{wks.location}/" .. bin_dir .. "/" .. outputdir .. "/%{prj.name}") -- i.e: "../Bin/Debug-Windows-x86_64/Crutch"
    objdir   ( "%{wks.location}/" .. obj_dir .. "/" .. outputdir .. "/%{prj.name}") -- i.e: "../Bin-Int/Debug-Windows-x86_64/Crutch"

    pchheader "chpch.h"
    pchsource (ROOT .. "Crutch/src/chpch.cpp")

    files {
        "%{wks.location}/%{prj.name}/src/**.h",
        "%{wks.location}/%{prj.name}/src/**.cpp",
        "%{wks.location}/%{prj.name}/vendor/glm/glm/**.hpp",
        "%{wks.location}/%{prj.name}/vendor/glm/glm/**.inl"
    }
    defines {
        "_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
    }

    includedirs {
		"%{wks.location}/%{prj.name}/src",
        "%{wks.location}/%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}"
    }
    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect      "C++17"
        staticruntime   "On"
        systemversion   "latest"

        defines { 
            --"CH_PLATFORM_WINDOWS", 
            --"CH_BUILD_DLL" 
            "GLFW_INCLUDE_NONE"
        }
        --postbuildcommands { 
            -- Copy the DLL into the sandbox .exe location. Must run initial build twice for the dir to exist.
            -- TODO Should figure out a premake way to avoid that? 
        --    ( "{COPY} %{cfg.buildtarget.relpath} ../" .. bin_dir .. "/" .. outputdir .. "/Sandbox") 
        --}

    filter "configurations:Debug"
        defines     "CH_DEBUG"
        symbols     "On"

    filter "configurations:Release"
        defines     "CH_RELEASE"
        optimize    "On"

----------------------------------
-- Sandbox Project (.exe)
----------------------------------
project "Sandbox"
    location      "%{wks.location}/Sandbox"
    kind          "ConsoleApp"
    language      "C++"
    cppdialect    "C++17"
    staticruntime "On"

    targetdir( "%{wks.location}/" .. bin_dir .. "/" .. outputdir .. "/%{prj.name}")
    objdir   ( "%{wks.location}/" .. obj_dir .. "/" .. outputdir .. "/%{prj.name}")

    files {
        "%{wks.location}/%{prj.name}/src/**.h",
        "%{wks.location}/%{prj.name}/src/**.cpp"
    }
    includedirs {
        "%{wks.location}/Crutch/vendor/spdlog/include",
        "%{wks.location}/Crutch/src"
    }
    links {
        "Crutch"
    }

    filter "system:windows"
        systemversion   "latest"

    filter "configurations:Debug"
        defines     "CH_DEBUG"
        runtime     "Debug"
        symbols     "On"

    filter "configurations:Release"
        defines     "CH_RELEASE"
        runtime     "Release"
        optimize    "On"
