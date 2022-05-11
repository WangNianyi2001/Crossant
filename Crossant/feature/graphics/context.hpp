#pragma once

#include "Crossant/common/event/subscriber.hpp"
#include "Crossant/common/type.hpp"
#include "target.hpp"

namespace Crossant::Graphics {
	struct Context {
		Target &target;

		Context(Target &target);
		virtual ~Context();

		virtual void MakeCurrent() const = 0;
		virtual void OnResize() = 0;
	};
}
