#pragma once

#include <algorithm>
#include <functional>

namespace Crossant {
	struct Operator {
#define DefBiOp(name, type, ret, expr)\
	static inline std::function<ret(type, type)> const name{ expr }
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
		static inline std::function<T(T, Pow)> const power{ [](T base, Pow pow) {
			return (T)std::pow(T, pow);
		} };
		TempHead static inline std::function<T(T)> const inverse{ [](T x) { return 1 / x; } };
		TempHead static inline std::function<T(T)> const square{ [](T x) { return x * x; } };

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
