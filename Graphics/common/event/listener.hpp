#pragma once

#include "subscriber.hpp"
#include <concepts>
#include <map>
#include <vector>

namespace Graphics {
	using namespace std;

	template<typename Type, typename Event>
	struct Listener : Subscriber<Event> {
	protected:
		using Handler = Subscriber<Event> *;
		map<Type, vector<Handler>> handlers;

	public:
		virtual void Push(Event event) const override {
			if(!handlers.contains(event.type))
				return;
			auto &listenersOfType = handlers.at(event.type);
			if(listenersOfType.size() <= 0)
				return;
			for(auto &listener : listenersOfType)
				listener->Push(event);
		}

		void Listen(Type type, Handler listener) {
			if(!handlers.contains(type))
				handlers[type] = vector<Handler>();
			handlers[type].push_back(listener);
		}

		void Listen(Type type, function<void(Event)> listener) {
			Listen(type, new ConfigurableSubscriber<Event>(listener));
		}
	};
}
