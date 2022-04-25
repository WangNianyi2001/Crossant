#pragma once

#include "subscriber.hpp"
#include <concepts>
#include <map>
#include <set>

namespace Graphics {
	using namespace std;

	template<typename Type, typename Event>
	class Listener : public Subscriber<Event> {
		using Handler = Subscriber<Event> *;
		map<Type, set<Handler>> handlers;

	public:
		virtual void Push(Event event) override {
			Type type = event.type;	// TODO
			if(!handlers.contains(type))
				return;
			set<Handler> listenersOfType = handlers[type];
			if(listenersOfType.size() <= 0)
				return;
			for(Handler listener : listenersOfType)
				listener->Push(event);
		}

		void Listen(Type type, Handler listener) {
			if(!handlers.contains(type))
				handlers[type] = set<Handler>();
			handlers[type].insert(listener);
		}

		void Listen(Type type, function<void(Event)> listener) {
			Listen(type, new ConfigurableSubscriber<Event>(listener));
		}
	};
}
