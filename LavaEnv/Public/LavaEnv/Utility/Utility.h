#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <tuple>

namespace LavaEnv::Utility {
	namespace Details {
		template <class From, class To>
		union UBCast {
			UBCast(From from) : m_From(from) { }

			From m_From;
			To m_To;
		};
	} // namespace Details

	template <class To, class From>
	To UBCast(From from) { return Details::UBCast<From, To>(from).m_To; }

	template <class R, class... Ts>
	using FunctionT = R (*)(Ts...);

	struct StringHash {
	public:
		using hash_type      = std::hash<std::string_view>;
		using is_transparent = void;

		std::size_t operator()(const char* str) const { return hash_type {}(str); }
		std::size_t operator()(std::string_view str) const { return hash_type {}(str); }
		std::size_t operator()(const std::string& str) const { return hash_type {}(str); }
	};
} // namespace LavaEnv::Utility