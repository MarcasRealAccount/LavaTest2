#pragma once

#include "../Flags.h"
#include "Field.h"
#include "Method.h"

#include <cstdint>

#include <string>
#include <vector>

namespace LavaEnv {
	class Class;

	namespace Register {
		struct Class {
		public:
			EClassFlags m_Flags = EClassFlag::None;
			std::string m_Id;
			std::vector<::LavaEnv::Class*> m_Supers;
			std::vector<Method> m_Methods;
			std::vector<Field> m_Fields;
			std::vector<std::uint8_t> m_Code;
		};
	} // namespace Register
} // namespace LavaEnv