#pragma once

#include "../Flags.h"
#include "../Utility/Utility.h"

#include <cstdint>

#include <string>

namespace LavaEnv::Register {
	struct Method {
	public:
		EMethodFlags m_Flags = EMethodFlag::None;
		std::string m_Id;
		std::uintptr_t m_Offset                = 0;
		Utility::FunctionT<void> m_FunctionPtr = nullptr;
	};
} // namespace LavaEnv::Register