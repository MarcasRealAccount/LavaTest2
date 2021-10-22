#pragma once

#include "ClassLoader.h"

#include <filesystem>
#include <string_view>

namespace LavaEnv {
	class DefaultClassLoader : public ClassLoader {
	public:
		LAVA_SYSV_ABI static DefaultClassLoader& Get();
		LAVA_SYSV_ABI static void Destroy();
		LAVA_SYSV_ABI static void Register();
		LAVA_SYSV_ABI static void Deregister();

	public:
		LAVA_SYSV_ABI virtual bool canLoadClass(std::string_view id) const override;
		LAVA_SYSV_ABI virtual Class* loadClass(std::string_view id) const override;

		LAVA_SYSV_ABI std::filesystem::path findClass(std::string_view id) const;

		LAVA_SYSV_ABI void setPreloadRequiredClasses(bool preloadRequiredClasses) { m_PreloadRequiredClasses = preloadRequiredClasses; }
		LAVA_SYSV_ABI void addClassPath(const std::filesystem::path& classPath);
		LAVA_SYSV_ABI void removeClassPath(const std::filesystem::path& classPath);

	private:
		DefaultClassLoader();
		~DefaultClassLoader() = default;

		DefaultClassLoader(const DefaultClassLoader&) = delete;
		DefaultClassLoader& operator=(const DefaultClassLoader&) = delete;

	private:
		bool m_PreloadRequiredClasses = false;
		std::vector<std::filesystem::path> m_ClassPaths;
	};
} // namespace LavaEnv