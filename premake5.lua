workspace("LavaTest2")
	configurations({ "Debug", "Release", "Dist" })
	platforms({ "x64" })
	
	cppdialect("C++20")
	rtti("Off")
	exceptionhandling("On")
	flags("MultiProcessorCompile")
	
	filter("configurations:Debug")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_DEBUG" })
		optimize("Off")
		symbols("On")
	
	filter("configurations:Release")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_RELEASE" })
		optimize("Full")
		symbols("On")
	
	filter("configurations:Dist")
		defines({ "LAVA_CONFIG=LAVA_CONFIG_DIST" })
		optimize("Full")
		symbols("Off")
	
	filter("system:windows")
		toolset("msc")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_WINDOWS" })
	
	filter("system:macos")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_MACOS" })
	
	filter("system:linux")
		defines({ "LAVA_SYSTEM=LAVA_SYSTEM_LINUX" })
	
	filter("toolset:msc")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_MSVC" })
	
	filter("toolset:gcc")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_GCC" })
	
	filter("toolset:clang")
		defines({ "LAVA_TOOLSET=LAVA_TOOLSET_CLANG" })
	
	filter("platforms:x64")
		defines({ "LAVA_PLATFORM=LAVA_PLATFORM_AMD64" })
	
	filter({})
	
	startproject("LavaTest")
	project("LavaEnv")
		kind("StaticLib")
		location("%{wks.location}/%{prj.name}/")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Bin/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}")
		
		includedirs({
			"%{prj.location}/Public/",
			"%{prj.location}/Private/"
		})
		
		files({ "%{prj.location}/**" })
		removefiles({ "**.vcxproj", "**.vcxproj.*", "**/Makefile", "**.make" })
	
	project("LavaTest")
		kind("ConsoleApp")
		location("%{wks.location}/%{prj.name}/")
		targetdir("%{wks.location}/Bin/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/")
		objdir("%{wks.location}/Bin/Int/%{cfg.system}-%{cfg.platform}-%{cfg.buildcfg}/%{prj.name}")
		debugdir("%{prj.location}/Run/")
		
		links({ "LavaEnv" })
		sysincludedirs({ "%{wks.location}/LavaEnv/Public/" })
		
		includedirs({
			"%{prj.location}/Public/",
			"%{prj.location}/Private/"
		})
		
		files({ "%{prj.location}/**" })
		removefiles({ "**.vcxproj", "**.vcxproj.*", "**/Makefile", "**.make" })
	