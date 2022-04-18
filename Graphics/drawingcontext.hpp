#pragma once

namespace Graphics {
	template<typename Target>
	class DrawingContext {
	protected:
		virtual void Dispose() = 0;
	public:
		virtual ~DrawingContext() = default;
		virtual void SetTarget(Target const &target) = 0;
		virtual void Render() = 0;
		virtual void SetSize(int width, int height) = 0;
	};
}
