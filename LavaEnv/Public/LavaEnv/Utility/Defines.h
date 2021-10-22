#pragma once

#define LAVA_SYSTEM_UNKNOWN 0
#define LAVA_SYSTEM_WINDOWS 1
#define LAVA_SYSTEM_UNIX 2
#define LAVA_SYSTEM_LINUX LAVA_SYSTEM_UNIX | 1
#define LAVA_SYSTEM_MACOS LAVA_SYSTEM_UNIX | 2

#define LAVA_TOOLSET_UNKNOWN 0
#define LAVA_TOOLSET_MSVC 1
#define LAVA_TOOLSET_CLANG 2
#define LAVA_TOOLSET_GCC 3

#define LAVA_CONFIG_UNKNOWN 0
#define LAVA_CONFIG_DEBUG 1
#define LAVA_CONFIG_DIST 2
#define LAVA_CONFIG_RELEASE LAVA_CONFIG_DEBUG | LAVA_CONFIG_DIST

#define LAVA_PLATFORM_UNKNOWN 0
#define LAVA_PLATFORM_AMD64 1

#define LAVA_FLAG(FLAGS, FLAG) ((FLAGS & FLAG) == FLAG)

#define LAVA_SYSTEM_IS_WINDOWS LAVA_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_WINDOWS)
#define LAVA_SYSTEM_IS_UNIX LAVA_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_UNIX)
#define LAVA_SYSTEM_IS_LINUX LAVA_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_LINUX)
#define LAVA_SYSTEM_IS_MACOS LAVA_FLAG(LAVA_SYSTEM, LAVA_SYSTEM_MACOS)

#define LAVA_TOOLSET_IS_MSVC LAVA_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_MSVC)
#define LAVA_TOOLSET_IS_CLANG LAVA_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_CLANG)
#define LAVA_TOOLSET_IS_GCC LAVA_FLAG(LAVA_TOOLSET, LAVA_TOOLSET_GCC)

#define LAVA_CONFIG_IS_DEBUG LAVA_FLAG(LAVA_CONFIG, LAVA_CONFIG_DEBUG)
#define LAVA_CONFIG_IS_DIST LAVA_FLAG(LAVA_CONFIG, LAVA_CONFIG_DIST)

#define LAVA_PLATFORM_IS_AMD64 LAVA_FLAG(LAVA_PLATFORM, LAVA_PLATFORM_AMD64)

#if LAVA_PLATFORM_IS_AMD64 && (LAVA_SYSTEM_IS_WINDOWS || LAVA_SYSTEM_IS_UNIX)
	#if LAVA_TOOLSET_IS_MSVC
		#define LAVA_SYSV_ABI __declspec(sysv_abi)
		#error MSVC Doesn't support SYSV AMD64 ABI compilation sadly, please report this to them :)
	#elif LAVA_TOOLSET_IS_CLANG || LAVA_TOOLSET_IS_GCC
		#define LAVA_SYSV_ABI __attribute__((sysv_abi))
	#else
		#define LAVA_SYSV_ABI
		#error Your toolset isn't currently supported, please open an issue on Github with information on the toolset (Compiler & Linker).
	#endif
#else
	#error Your platform isn't supported, please open an issue on Github with information on the platform (Architecture & System).
#endif