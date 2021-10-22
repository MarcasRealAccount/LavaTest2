#pragma once

#include "Flags.h"
#include "Object.h"
#include "Register/Method.h"
#include "Utility/Defines.h"
#include "Utility/Utility.h"

#include <string>
#include <utility>

namespace LavaEnv {
	class Class;

	class Method {
	public:
		friend Class;

	public:
		Method();
		~Method() = default;

		LAVA_SYSV_ABI auto getFlags() const { return m_Flags; }
		LAVA_SYSV_ABI auto getClass() const { return m_Class; }
		LAVA_SYSV_ABI auto& getId() const { return m_Id; }

		template <class R, class... Ts>
		LAVA_SYSV_ABI R invokeStatic(Ts&&... ts) {
			return Utility::UBCast<Utility::FunctionT<R, Ts...>>(m_FunctionPtr)(std::forward<Ts>(ts)...);
		}

		template <class R, class... Ts>
		LAVA_SYSV_ABI R invoke(Object* object, Ts&&... ts) {
			return Utility::UBCast<Utility::FunctionT<R, void*, Ts...>>(m_FunctionPtr)(object, std::forward<Ts>(ts)...);
		}

	private:
		Method(Class* clazz, Register::Method&& method);

	private:
		EMethodFlags m_Flags;
		Class* m_Class;
		std::string m_Id;
		Utility::FunctionT<void> m_FunctionPtr;
	};
} // namespace LavaEnv