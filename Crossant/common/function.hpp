#pragma once

#include <algorithm>
#include <functional>

namespace Crossant {
	template<typename Ret, typename ...Args>
	struct Function {
		virtual Ret operator()(Args ...arguments) const = 0;
	};

	template<typename Ret, typename ...Args>
	struct FunctionRef : Function<Ret, Args...> {
		std::function<Ret(Args ...)> ref;

		FunctionRef(std::function<Ret(Args ...)> const &ref) : ref(ref) {}

		virtual Ret operator()(Args ...arguments) const override {
			return ref(arguments...);
		}
	};

	struct Operator {
#define DefBiOp(name, type, ret, expr)\
	static inline FunctionRef<ret, type, type> const name{ expr }
#define DefLambdaBiOp(name, type, ret, expr) DefBiOp(name, type, ret, [](type a, type b) { return expr; })
#define TempHead template<typename T>
#define DefTempBiOp(name, ret, expr) TempHead DefLambdaBiOp(name, T, ret, expr)

#define DefBiArith(name, op) DefTempBiOp(name, T, a op b)
		DefBiArith(plus, +);
		DefBiArith(minus, -);
		DefBiArith(multiply, *);
		DefBiArith(divide, / );
#undef DefBiArith

		template<typename T, typename Pow = unsigned>
		static inline FunctionRef<T, T, Pow> const power{ [](T base, Pow pow) {
			return (T)std::pow(T, pow);
		} };
		TempHead static inline FunctionRef<T, T> const inverse{ [](T x) { return 1 / x; } };
		TempHead static inline FunctionRef<T, T> const square{ [](T x) { return x * x; } };

		TempHead DefLambdaBiOp(min, T, T, std::min(a, b));
		TempHead DefLambdaBiOp(max, T, T, std::max(a, b));

#define DefBiComp(name, op) DefTempBiOp(name, bool, a op b)
		DefBiComp(equal, == );
		DefBiComp(inequal, != );
		DefBiComp(less, < );
		DefBiComp(greater, > );
		DefBiComp(lessEqual, <= );
		DefBiComp(greaterEqual, >= );
#undef DefBiComp

#define DefLogicComp(name, op) DefLambdaBiOp(name, bool, bool, a op b)
		DefLogicComp(logicAnd, &&);
		DefLogicComp(logicOr, || );
#undef DefLogicComp

#undef DefTempBiOp
#undef TempHead
#undef DefLambdaBiOp
#undef DefBiOp
	};
}
