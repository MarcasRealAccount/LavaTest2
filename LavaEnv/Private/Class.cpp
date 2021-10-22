#include "LavaEnv/Class.h"

#include <cstdlib>

#include <string_view>

namespace LavaEnv {
	Method* Class::getMethod(std::string_view id) const {
		for (auto& method : m_Methods)
			if (method.m_Id == id)
				return const_cast<Method*>(&method);
		return nullptr;
	}

	Field* Class::getField(std::string_view id) const {
		for (auto& field : m_Fields)
			if (field.m_Id == id)
				return const_cast<Field*>(&field);
		return nullptr;
	}

	Object* Class::instantiateHeap() {
		std::size_t totalClassSize = 0;

		void* memory = std::malloc(sizeof(Object) + totalClassSize);

		*reinterpret_cast<Class**>(memory) = this;

		return reinterpret_cast<Object*>(memory);
	}

	void Class::destroyHeap(Object* object) {
		std::free(object);
	}
} // namespace LavaEnv