#include "LavaEnv/ClassRegistry.h"

namespace LavaEnv {
	ClassRegistry& ClassRegistry::Get() {
		static ClassRegistry* registry = new ClassRegistry();
		return *registry;
	}

	void ClassRegistry::Destroy() {
		delete &Get();
	}

	Class* ClassRegistry::getClass(std::string_view id) const {
		m_Classes.find(id);
	}
} // namespace LavaEnv