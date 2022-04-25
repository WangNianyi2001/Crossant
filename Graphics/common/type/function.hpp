#pragma once

namespace Graphics {
	template<typename Ret, typename ...Args>
	struct Function {
		virtual Ret operator()(Args const &...arguments) const = 0;
	};

	template<typename To, typename From>
	struct TypeConverter : Function<To, From> {
		virtual To operator()(From const &value) const override {
			return (To)value;
		}
	};

#pragma region BinaryOperator
	template<typename Ret, typename A = Ret, typename B = A>
	using BinaryOperator = Function<Ret, A, B>;

#define BINARY_OPERATOR(name, expr)\
	template<typename Ret, typename A = Ret, typename B = A>\
	struct name : BinaryOperator<A, B> {\
		virtual Ret operator()(A const &a, B const &b) const {\
			return (expr);\
		}\
	}
	BINARY_OPERATOR(Plus, a + b);
	BINARY_OPERATOR(Minus, a - b);
	BINARY_OPERATOR(Multiply, a * b);
	BINARY_OPERATOR(Divide, a / b);
	BINARY_OPERATOR(Max, a > b ? a : b);
	BINARY_OPERATOR(Min, a < b ? a : b);
#undef BINARY_OPERATOR
#pragma endregion

#pragma region BinaryRelation
	template<typename Type>
	using BinaryRelation = Function<bool, Type, Type>;

#define BINARY_RELATION(name, expr)\
	template<typename Type>\
	struct name : BinaryRelation<Type> {\
		virtual bool operator()(Type const &a, Type const &b) const {\
			return (expr);\
		}\
	}
	BINARY_RELATION(Equal, a == b);
	BINARY_RELATION(Inequal, a != b);
	BINARY_RELATION(Less, a < b);
	BINARY_RELATION(Greater, a > b);
	BINARY_RELATION(LessEqual, a <= b);
	BINARY_RELATION(GreaterEqual, a >= b);
#undef BINARY_RELATION
#pragma endregion

#pragma region Folder
	template<typename Ret, typename Type = Ret>
	struct Folder : Function<Ret, Type, Type> {
		Ret const unit;

		Folder(Ret unit) : unit(unit) {}
	};

#define FOLDER(name, op, def)\
	template<typename Ret, typename Type>\
	struct name : Folder<Ret, Type> {\
		name() : Folder<Ret, Type>(def) {}\
		virtual Ret operator()(Type const &a, Type const &b) const{\
			return a op b;\
		}\
	}
	FOLDER(And, &&, true);
	FOLDER(Or, || , false);
#undef FOLDER
#pragma endregion
}
