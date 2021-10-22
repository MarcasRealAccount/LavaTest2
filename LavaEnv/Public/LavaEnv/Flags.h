#pragma once

#include "Utility/Defines.h"

#include <cstddef>
#include <cstdint>

#include <ostream>
#include <string>

namespace LavaEnv {
	template <class T>
	class EFlags {
	public:
		constexpr EFlags(T value) : m_Value(value) { }
		template <class U>
		constexpr EFlags(const EFlags<U>& flags) : m_Value(flags.m_Value) { }

		LAVA_SYSV_ABI constexpr operator T() const { return m_Value; }

		LAVA_SYSV_ABI constexpr T getValue() const { return m_Value; }

		LAVA_SYSV_ABI constexpr void setValue(T value) { m_Value = value; }

		template <class U>
		LAVA_SYSV_ABI constexpr bool isFlag(EFlags<U> other) const { return (m_Value & other.m_Value) == other.m_Value; }

		template <class U>
		LAVA_SYSV_ABI constexpr EFlags<T>& operator=(const EFlags<U>& flags) {
			m_Value = flags.m_Value;
			return *this;
		}

		LAVA_SYSV_ABI friend constexpr EFlags<T> operator~(EFlags<T> flags) { return ~flags.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator==(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value == rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator!=(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value != rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator<(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value < rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator>(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value > rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator<=(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value <= rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr bool operator>=(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value >= rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI friend constexpr EFlags<T> operator&(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value & rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI constexpr EFlags<T>& operator&=(EFlags<U> other) {
			m_Value &= other.m_Value;
			return *this;
		}
		template <class U>
		LAVA_SYSV_ABI friend constexpr EFlags<T> operator|(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value | rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI constexpr EFlags<T>& operator|=(EFlags<U> other) {
			m_Value |= other.m_Value;
			return *this;
		}
		template <class U>
		LAVA_SYSV_ABI friend constexpr EFlags<T> operator^(EFlags<T> lhs, EFlags<U> rhs) { return lhs.m_Value ^ rhs.m_Value; }
		template <class U>
		LAVA_SYSV_ABI constexpr EFlags<T>& operator^=(EFlags<U> other) {
			m_Value ^= other.m_Value;
			return *this;
		}
		LAVA_SYSV_ABI friend constexpr EFlags<T> operator<<(EFlags<T> lhs, std::size_t count) { return lhs.m_Value << count; }
		LAVA_SYSV_ABI friend constexpr EFlags<T> operator>>(EFlags<T> lhs, std::size_t count) { return lhs.m_Value >> count; }
		LAVA_SYSV_ABI constexpr EFlags<T>& operator<<=(std::size_t count) {
			m_Value <<= count;
			return *this;
		}
		LAVA_SYSV_ABI constexpr EFlags<T>& operator>>=(std::size_t count) {
			m_Value >>= count;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& stream, EFlags<T> flags) { return stream << m_Value; }

	protected:
		T m_Value;
	};

	class EClassFlags : public EFlags<std::uint16_t> {
	public:
		constexpr EClassFlags(std::uint16_t value) : EFlags(value) { }

		LAVA_SYSV_ABI std::string toString() const;

		LAVA_SYSV_ABI friend std::ostream& operator<<(std::ostream& stream, EClassFlags flags) { return stream << flags.toString(); }
	};

	class EMethodFlags : public EFlags<std::uint16_t> {
	public:
		constexpr EMethodFlags(std::uint16_t value) : EFlags(value) { }

		LAVA_SYSV_ABI std::string toString() const;

		LAVA_SYSV_ABI friend std::ostream& operator<<(std::ostream& stream, EMethodFlags flags) { return stream << flags.toString(); }
	};

	class EFieldFlags : public EFlags<std::uint16_t> {
	public:
		constexpr EFieldFlags(std::uint16_t value) : EFlags(value) { }

		LAVA_SYSV_ABI std::string toString() const;

		LAVA_SYSV_ABI friend std::ostream& operator<<(std::ostream& stream, EFieldFlags flags) { return stream << flags.toString(); }
	};

	namespace EClassFlag {
		static constexpr EClassFlags None   = 0;
		static constexpr EClassFlags Static = 1;
	} // namespace EClassFlag

	namespace EMethodFlag {
		static constexpr EMethodFlags None  = 0;
		static constexpr EClassFlags Static = 1;
	} // namespace EMethodFlag

	namespace EFieldFlag {
		static constexpr EFieldFlags None   = 0;
		static constexpr EClassFlags Static = 1;
	} // namespace EFieldFlag

	std::string EClassFlags::toString() const {
		if (*this == EClassFlag::None)
			return "None";

		EClassFlags flags = *this;
		std::string flagsStr;
		if (flags.isFlag(EClassFlag::Static)) {
			flags &= ~EClassFlag::Static;
			if (!flagsStr.empty())
				flagsStr += " | ";
			flagsStr += "Static";
		}

		if (flags.m_Value != 0)
			flagsStr = '(' + flagsStr + ") + " + std::to_string(flags.m_Value);
		return flagsStr;
	}

	std::string EMethodFlags::toString() const {
		if (*this == EMethodFlag::None)
			return "None";

		EMethodFlags flags = *this;
		std::string flagsStr;
		if (flags.isFlag(EMethodFlag::Static)) {
			flags &= ~EMethodFlag::Static;
			if (!flagsStr.empty())
				flagsStr += " | ";
			flagsStr += "Static";
		}

		if (flags.m_Value != 0)
			flagsStr = '(' + flagsStr + ") + " + std::to_string(flags.m_Value);
		return flagsStr;
	}

	std::string EFieldFlags::toString() const {
		if (*this == EFieldFlag::None)
			return "None";

		EFieldFlags flags = *this;
		std::string flagsStr;
		if (flags.isFlag(EFieldFlag::Static)) {
			flags &= ~EFieldFlag::Static;
			if (!flagsStr.empty())
				flagsStr += " | ";
			flagsStr += "Static";
		}

		if (flags.m_Value != 0)
			flagsStr = '(' + flagsStr + ") + " + std::to_string(flags.m_Value);
		return flagsStr;
	}
} // namespace LavaEnv