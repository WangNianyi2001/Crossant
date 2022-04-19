#pragma once

#include <functional>

namespace Graphics {
	template<typename ...Args>
	struct Subscriber {
		virtual bool Push(Args ...arguments) = 0;
		virtual ~Subscriber() = default;
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

		virtual bool Push(Args ...arguments) override {
			if(!action)
				return false;
			action(arguments...);
			return true;
		}

		void Configure(std::function<void(Args ...)> action) {
			this->action = action;
		}
	};
}
