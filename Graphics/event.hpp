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
		virtual bool Fire(Event event) = 0;
	};

	template<typename Type, derived_from<Event<Type>> Event>
	class EventHandler : public EventTarget<Type, Event> {
		function<void(Event)> const callable;

	public:
		EventHandler(function<void(Event)> callable) : callable(callable) {}

		virtual bool Fire(Event event) override {
			callable(event);
			return true;
		}
	};

	template<typename Type, derived_from<Event<Type>> Event>
	class EventDistributor : public EventTarget<Type, Event> {
		using Listener = EventTarget<Type, Event>;
		map<Type, set<Listener *>> listeners;

	public:
		virtual bool Fire(Event event) override {
			auto type = listeners.find(event.type);
			if(type == listeners.end())
				return false;
			for(auto receiver : type->second)
				receiver->Fire(event);
			return true;
		}

		void Listen(Type type, Listener *listener) {
			listeners[type].insert(listener);
		}

		void Listen(Type type, function<void(Event)> listener) {
			Listen(type, new EventHandler<Type, Event>(listener));
		}
	};
}
