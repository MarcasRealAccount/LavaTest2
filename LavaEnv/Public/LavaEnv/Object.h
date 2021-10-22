#pragma once

#include "Class.h"
#include "Utility/Defines.h"

namespace LavaEnv {
	struct Object {
	public:
		LAVA_SYSV_ABI auto getClass() const { return m_Class; }

	private:
		Class* m_Class;
	};
} // namespace LavaEnv