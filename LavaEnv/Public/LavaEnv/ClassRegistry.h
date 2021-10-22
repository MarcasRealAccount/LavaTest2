#pragma once

#include "Class.h"
#include "ClassLoader.h"
#include "Register/Class.h"
#include "Utility/Defines.h"
#include "Utility/Utility.h"

#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace LavaEnv {
	class ClassRegistry {
	public:
		LAVA_SYSV_ABI static ClassRegistry& Get();
		LAVA_SYSV_ABI static void Destroy();

	public:
		LAVA_SYSV_ABI auto& getClasses() const { return m_Classes; }

		LAVA_SYSV_ABI Class* getClass(std::string_view id) const;
		LAVA_SYSV_ABI Class* getClassC(const char* id) const { return getClass(id); }

		LAVA_SYSV_ABI Class* registerClass(Register::Class&& clazz);
		LAVA_SYSV_ABI void deregisterClass(std::string_view id);
		LAVA_SYSV_ABI void deregisterClassC(const char* id) { deregisterClass(id); }

		LAVA_SYSV_ABI void registerClassLoader(ClassLoader* classLoader);
		LAVA_SYSV_ABI void deregisterClassLoader(ClassLoader* classLoader);

		LAVA_SYSV_ABI Class* loadClass(std::string_view id);
		LAVA_SYSV_ABI Class* loadClassC(const char* id) { return loadClass(id); }

	private:
		ClassRegistry() = default;
		~ClassRegistry();

		ClassRegistry(const ClassRegistry&) = delete;
		ClassRegistry& operator=(const ClassRegistry&) = delete;

	private:
		std::unordered_set<ClassLoader*> m_ClassLoaders;
		std::unordered_map<std::string, Class*, Utility::StringHash, std::equal_to<>> m_Classes;
	};
} // namespace LavaEnv