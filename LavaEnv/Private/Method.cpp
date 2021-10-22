#include "LavaEnv/Method.h"

namespace LavaEnv {
	Method::Method()
	    : m_Flags(EMethodFlag::None), m_Class(nullptr), m_FunctionPtr(nullptr) { }

	Method::Method(Class* clazz, Register::Method&& method) : m_Flags(method.m_Flags), m_Class(clazz), m_Id(std::move(method.m_Id)) {
		if (method.m_Offset)
			m_FunctionPtr = Utility::UBCast<Utility::FunctionT<void>>(reinterpret_cast<char*>(m_Class->getCode().getMemory()) + method.m_Offset);
		else
			m_FunctionPtr = std::move(method.m_FunctionPtr);
	}
} // namespace LavaEnv