#pragma once

#include "Flags.h"
#include "Object.h"
#include "Register/Field.h"
#include "Utility/Defines.h"

#include <cstdint>

#include <string>

namespace LavaEnv {
	class Class;

	class Field {
	public:
		friend Class;

	public:
		Field();
		~Field() = default;

		LAVA_SYSV_ABI auto getFlags() const { return m_Flags; }
		LAVA_SYSV_ABI auto getClass() const { return m_Class; }
		LAVA_SYSV_ABI auto& getId() const { return m_Id; }
		LAVA_SYSV_ABI auto getOffset() const { return m_Offset; }

		template <class T>
		LAVA_SYSV_ABI T& getStatic() {
			return *reinterpret_cast<T*>(m_Class->getData().data() + m_Offset);
		}

		template <class T>
		LAVA_SYSV_ABI T& get(Object* object) {
			return *reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(object) + sizeof(Object) + m_Offset);
		}

		template <class T>
		LAVA_SYSV_ABI T& setStatic(T&& value) {
			return getStatic<T>() = std::forward<T>(value);
		}

		template <class T>
		LAVA_SYSV_ABI T& set(Object* object, T&& value) {
			return get<T>(object) = std::forward<T>(value);
		}

	private:
		Field(Class* clazz, Register::Field&& field);

	private:
		EFieldFlags m_Flags;
		Class* m_Class;
		std::string m_Id;
		std::uintptr_t m_Offset;
	};
} // namespace LavaEnv