#pragma once

#include "tuple.hpp"

namespace Graphics {
	template<typename Ret, typename ...Args>
	struct Function {
		virtual Ret operator()(Args const &...arguments) const = 0;
	};

	template<typename Type>
	using Transform = Function<Type, Type>;

#pragma region BinaryOperator
	template<typename Type>
	using BinaryOperator = Function<Type, Type, Type>;

#define BINARY_OPERATOR(name, op)\
	template<typename Type>\
	struct name : BinaryOperator<Type> {\
		virtual Type operator()(Type const &a, Type const &b) const{\
			return a op b;\
		}\
	}
	BINARY_OPERATOR(Plus, +);
	BINARY_OPERATOR(Minus, -);
	BINARY_OPERATOR(Multiply, *);
	BINARY_OPERATOR(Divide, /);
#undef BINARY_OPERATOR
#pragma endregion

#pragma region BinaryRelation
	template<typename Type>
	using BinaryRelation = Function<bool, Type, Type>;

#define BINARY_RELATION(name, op)\
	template<typename Type>\
	struct name : BinaryRelation<Type> {\
		virtual bool operator()(Type const &a, Type const &b) const{\
			return a op b;\
		}\
	}
	BINARY_RELATION(Equal, == );
	BINARY_RELATION(Inequal, != );
	BINARY_RELATION(Less, < );
	BINARY_RELATION(Greater, > );
	BINARY_RELATION(LessEqual, <= );
	BINARY_RELATION(GreaterEqual, >= );
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
