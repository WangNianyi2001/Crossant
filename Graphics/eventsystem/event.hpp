#pragma once

#include "subscriber.hpp"
#include <concepts>
#include <map>
#include <set>

namespace Graphics {
	using namespace std;

	template<typename Type, typename Event>
	class EventListener : public Subscriber<Event> {
		using Listener = Subscriber<Event> *;
		map<Type, set<Listener>> listeners;

	public:
		virtual bool Push(Event event) override {
			Type type = event.type;	// TODO
			if(!listeners.contains(type))
				return false;
			set<Listener> listenersOfType = listeners[type];
			if(listenersOfType.size() <= 0)
				return false;
			for(Listener listener : listenersOfType)
				listener->Push(event);
			return true;
		}

		void Listen(Type type, Listener listener) {
			if(!listeners.contains(type))
				listeners[type] = set<Listener>();
			listeners[type].insert(listener);
		}

		void Listen(Type type, function<void(Event)> listener) {
			Listen(type, new ConfigurableSubscriber<Event>(listener));
		}
	};
}
