#pragma once

namespace Graphics {
	template<unsigned i, typename _Type, typename ...Rest>
	struct TupleType {
		using Type = TupleType<i - 1, Rest ...>::Type;
	};

	template<typename _Type, typename ...Rest>
	struct TupleType<0, _Type, Rest ...> {
		using Type = _Type;
	};

	template<typename ...Types>
	struct Tuple;

	template<typename First, typename ...Rest>
	struct Tuple<First, Rest ...> {
		using Type = First;

		First value;
		Tuple<Rest ...> rest;

		Tuple(First value, Rest ...rest) :
			value(value),
			rest(Tuple<Rest ...>(rest...)) {
		}

		template<unsigned i>
		inline TupleType<i, First, Rest...>::Type &Get() {
			if constexpr(i == 0U)
				return value;
			else
				return rest.Tuple<Rest ...>::Get<i - 1>();
		}

		template<unsigned i>
		inline TupleType<i, First, Rest...>::Type Get() const {
			if constexpr(i == 0U)
				return value;
			else
				return rest.Tuple<Rest ...>::Get<i - 1>();
		}
	};

	template<>
	struct Tuple<> {
		using Type = void;

		Tuple() = default;
	};
}
