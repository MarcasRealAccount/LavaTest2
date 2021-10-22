#pragma once

#include "Field.h"
#include "Flags.h"
#include "Method.h"
#include "Register/Class.h"
#include "Utility/Defines.h"
#include "Utility/Memory.h"

#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace LavaEnv {
	struct Object;

	class Class {
	public:
		friend class ClassRegistry;

	public:
		~Class() = default;

		LAVA_SYSV_ABI auto getFlags() const { return m_Flags; }
		LAVA_SYSV_ABI auto& getId() const { return m_Id; }
		LAVA_SYSV_ABI auto& getSupers() const { return m_Supers; }
		LAVA_SYSV_ABI auto& getMethods() const { return m_Methods; }
		LAVA_SYSV_ABI auto& getFields() const { return m_Fields; }
		LAVA_SYSV_ABI auto& getCode() const { return m_Code; }
		LAVA_SYSV_ABI auto& getData() const { return m_Data; }

		LAVA_SYSV_ABI Method* getMethod(std::string_view id) const;
		LAVA_SYSV_ABI Method* getMethodC(const char* id) const { return getMethod(id); }

		LAVA_SYSV_ABI Field* getField(std::string_view id) const;
		LAVA_SYSV_ABI Field* getFieldC(const char* id) const { return getField(id); }

		LAVA_SYSV_ABI Object* instantiateHeap();
		LAVA_SYSV_ABI void destroyHeap(Object* object);

		template <class R, class... Ts>
		LAVA_SYSV_ABI R invokeStaticMethod(std::string_view id, Ts&&... ts) {
			Method* method = getMethod(id);
			if constexpr (!std::is_void_v<R>)
				if (method == nullptr)
					throw std::runtime_error("Class '" + m_Id + "' does not contain method '" + id + "'");
			return method->invokeStatic<R, Ts...>(std::forward<Ts>(ts)...);
		}

		template <class R, class... Ts>
		LAVA_SYSV_ABI R invokeMethod(std::string_view id, Object* object, Ts&&... ts) {
			Method* method = getMethod(id);
			if constexpr (!std::is_void_v<R>)
				if (method == nullptr)
					throw std::runtime_error("Class '" + m_Id + "' does not contain method '" + id + "'");
			return method->invoke<R, Ts...>(object, std::forward<Ts>(ts)...);
		}

		template <class T>
		LAVA_SYSV_ABI T& getStatic(std::string_view id) {
			Field* field = getField(id);
			if (field == nullptr)
				throw std::runtime_error("Class '" + m_Id + "' does not contain field '" + id + "'");
			return field->getStatic<T>();
		}

		template <class T>
		LAVA_SYSV_ABI T& get(std::string_view id, Object* object) {
			Field* field = getField(id);
			if (field == nullptr)
				throw std::runtime_error("Class '" + m_Id + "' does not contain field '" + id + "'");
			return field->get<T>(object);
		}

		template <class T>
		LAVA_SYSV_ABI T& setStatic(std::string_view id, T&& value) {
			Field* field = getField(id);
			if (field == nullptr)
				throw std::runtime_error("Class '" + m_Id + "' does not contain field '" + id + "'");
			return field->setStatic<T>(std::forward<T>(value));
		}

		template <class T>
		LAVA_SYSV_ABI T& set(std::string_view id, Object* object, T&& value) {
			Field* field = getField(id);
			if (field == nullptr)
				throw std::runtime_error("Class '" + m_Id + "' does not contain field '" + id + "'");
			return field->set<T>(object, std::forward<T>(value));
		}

	private:
		Class(Register::Class&& clazz);
		Class(const Class&) = delete;
		Class& operator=(const Class&) = delete;

	private:
		EClassFlags m_Flags;
		std::string m_Id;
		std::vector<Class*> m_Supers;
		std::vector<Method> m_Methods;
		std::vector<Field> m_Fields;
		Utility::ExecutableMemory m_Code;
		std::vector<std::uint8_t> m_Data;
	};
} // namespace LavaEnv