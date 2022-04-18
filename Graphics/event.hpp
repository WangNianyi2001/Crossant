#pragma once

#include <functional>
#include <concepts>
#include <map>
#include <set>

namespace Graphics {
	using namespace std;

	template<typename Type>
	struct Event {
		Type type;

		virtual bool operator==(Event<Type> other) {
			return type == other.type;
		}
	};

	template<typename Type, derived_from<Event<Type>> Event>
	class EventTarget {
	public:
		virtual void Fire(Event event) = 0;
	};

	template<typename Type, derived_from<Event<Type>> Event>
	class EventHandler : public EventTarget<Type, Event> {
		function<void(Event)> const callable;

	public:
		EventHandler(function<void(Event)> callable) : callable(callable) {}

		virtual void Fire(Event event) override {
			callable(event);
		}
	};

	template<typename Type, derived_from<Event<Type>> Event>
	class EventDistributor : public EventTarget<Type, Event> {
		using Listener = EventTarget<Type, Event>;
		map<Type, set<Listener *>> listeners;

	public:
		bool HasListener(Type type) {
			return listeners.find(type) != listeners.end();
		}

		virtual void Fire(Event event) override {
			if(!HasListener(event.type))
				return;
			for(auto receiver : listeners.find(event.type)->second)
				receiver->Fire(event);
		}

		void Listen(Type type, Listener *listener) {
			listeners[type].insert(listener);
		}

		void Listen(Type type, function<void(Event)> listener) {
			Listen(type, new EventHandler<Type, Event>(listener));
		}
	};
}
