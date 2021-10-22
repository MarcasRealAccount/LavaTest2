#include "LavaEnv/Field.h"

namespace LavaEnv {
	Field::Field()
	    : m_Flags(EFieldFlag::None), m_Class(nullptr), m_Offset(0) { }

	Field::Field(Class* clazz, Register::Field&& field)
	    : m_Flags(field.m_Flags), m_Class(clazz), m_Id(std::move(field.m_Id)), m_Offset(field.m_Offset) { }
} // namespace LavaEnv