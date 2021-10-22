#pragma once

#include "Class.h"
#include "Utility/Defines.h"

#include <string_view>

namespace LavaEnv {
	class ClassLoader {
	public:
		LAVA_SYSV_ABI virtual bool canLoadClass(std::string_view id) const = 0;
		LAVA_SYSV_ABI virtual Class* loadClass(std::string_view id) const  = 0;
	};
} // namespace LavaEnv