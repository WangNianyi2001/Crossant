#pragma once

#include <concepts>

namespace Graphics {
	template<typename Target>
	class Context {
	protected:
		virtual void Dispose() = 0;
	public:
		virtual ~Context() = default;
		virtual void SetTarget(Target const &target) = 0;
		virtual void Render() = 0;
		virtual void SetSize(int width, int height) = 0;
	};
}
