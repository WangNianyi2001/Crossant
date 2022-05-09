#pragma once

#include <functional>

namespace Graphics {
	template<typename ...Args>
	struct Subscriber {
		virtual void Push(Args ...arguments) const = 0;
	};

	template<typename ...Args>
	struct ConfigurableSubscriber : Subscriber<Args ...> {
	protected:
		std::function<void(Args ...)> action;

	public:
		ConfigurableSubscriber(std::function<void(Args ...)> action) {
			Configure(action);
		}
		ConfigurableSubscriber() : ConfigurableSubscriber(nullptr) {}

		virtual void Push(Args ...arguments) const override {
			if(!action)
				return;
			action(arguments...);
		}

		void Configure(std::function<void(Args ...)> action) {
			this->action = action;
		}
	};
}
