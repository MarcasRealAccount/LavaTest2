#pragma once

#include "../Flags.h"
#include "../Utility/Utility.h"

#include <cstdint>

#include <string>

namespace LavaEnv::Register {
	struct Field {
	public:
		EFieldFlags m_Flags = EFieldFlag::None;
		std::string m_Id;
		std::uintptr_t m_Offset = 0;
	};
} // namespace LavaEnv::Register