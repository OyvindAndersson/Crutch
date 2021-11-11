
local ROOT = "../"
local bin_dir = "Binaries"
local obj_dir = "Binaries-Int"
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
	
IncludeDir = {}
    IncludeDir["GLFW"] = "%{wks.location}/Crutch/vendor/GLFW/include"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include (ROOT .. "Crutch/vendor/GLFW")
group ""

----------------------------------
-- Crutch Project (.dll)
----------------------------------
project "Crutch"
    location  "%{wks.location}/Crutch"
    --kind      "SharedLib"
	kind 	  "StaticLib"
	staticruntime "off"
    language  "C++"
    cppdialect "C++17"
    targetdir( "%{wks.location}/" .. bin_dir .. "/" .. outputdir .. "/%{prj.name}") -- i.e: "../Bin/Debug-Windows-x86_64/Crutch"
    objdir   ( "%{wks.location}/" .. obj_dir .. "/" .. outputdir .. "/%{prj.name}") -- i.e: "../Bin-Int/Debug-Windows-x86_64/Crutch"

    files {
        "%{wks.location}/%{prj.name}/src/**.h",
        "%{wks.location}/%{prj.name}/src/**.cpp"
    }
    includedirs {
		"%{wks.location}/%{prj.name}/src",
        "%{wks.location}/%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
    }
    links {
        "GLFW"
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
    location "%{wks.location}/Sandbox"
    kind     "ConsoleApp"
    language "C++"
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
        cppdialect      "C++17"
        staticruntime   "On"
        systemversion   "latest"

        defines { 
            --"CH_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines     "CH_DEBUG"
        symbols     "On"

    filter "configurations:Release"
        defines     "CH_RELEASE"
        optimize    "On"
