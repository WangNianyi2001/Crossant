#pragma once

#include "tuple.hpp"

namespace Graphics {
	template<typename Ret, typename ...Args>
	struct Function {
		virtual Ret operator()(Args const &...arguments) const = 0;
	};

	template<typename Type>
	using BinaryOperation = Function<Type, Type, Type>;

	struct BooleanOperation : BinaryOperation<bool> {
		struct And;
		struct Or;

		bool const unit;

		BooleanOperation(bool unit) : unit(unit) {}
	};

	struct BooleanOperation::And : BooleanOperation {
		And() : BooleanOperation(true) {}

		virtual constexpr bool operator()(bool const &a, bool const &b) const override {
			return a && b;
		}
	};

	struct BooleanOperation::Or : BooleanOperation {
		Or() : BooleanOperation(false) {}

		virtual constexpr bool operator()(bool const &a, bool const &b) const override {
			return a || b;
		}
	};

	template<typename Type>
	struct Comparator : Function<bool, Type, Type> {
		struct Equal;
		struct Less;
		struct Greater;
	};

	template<typename Type>
	struct Comparator<Type>::Equal : Comparator<Type> {
		virtual constexpr bool operator()(Type const &a, Type const &b) const override {
			return a == b;
		}
	};

	template<typename Type>
	struct Comparator<Type>::Less : Comparator<Type> {
		virtual constexpr bool operator()(Type const &a, Type const &b) const override {
			return a < b;
		}
	};

	template<typename Type>
	struct Comparator<Type>::Greater : Comparator<Type> {
		virtual constexpr bool operator()(Type const &a, Type const &b) const override {
			return a > b;
		}
	};
}
