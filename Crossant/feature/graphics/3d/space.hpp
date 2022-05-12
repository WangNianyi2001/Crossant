#pragma once

#include "context.hpp"
#include "Crossant/common/type/quaternion.hpp"
#include <set>
#include <concepts>

namespace Crossant::Graphics::Graphics3D {
	struct Transform {
		Transform *parent = nullptr;
		Coord3D translation{ 0, 0, 0 };
		Quaternion rotation{ 1, { 0, 0, 0 } };
		Coord3D scalor{ 1, 1, 1 };

		void Apply(Context &context) const {
			if(parent != nullptr)
				parent->Apply(context);
			context.Translate(translation);
			context.Rotate(rotation);
			context.Scale(scalor);
		}
	};

	struct Object;

	struct Space : Context {
		std::set<Object *> objects;

		Space(Target &target) : Context(target) {}

		virtual ~Space() {
			while(!objects.empty())
				delete *objects.begin();
		}
	};

	struct Component;

	struct Object {
		Space &space;
		Transform transform;
		std::set<Component *> components;

		Object(Space &space) : space(space) {
			space.objects.insert(this);
		}

		virtual ~Object() {
			while(!components.empty())
				delete *components.begin();
			auto self = space.objects.find(this);
			if(self != space.objects.end())
				space.objects.erase(self);
		}

		template<std::derived_from<Component> T>
		T *GetComponentOfType() {
			for(Component *component : components) {
				T *p = dynamic_cast<T *>(component);
				if(p != nullptr)
					return p;
			}
			return nullptr;
		}
	};

	struct Component {
		Object &object;

		Component(Object &object) : object(object) {
			object.components.insert(this);
		}

		virtual ~Component() {
			auto self = object.components.find(this);
			if(self != object.components.end())
				object.components.erase(self);
		}
	};
}