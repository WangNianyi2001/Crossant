#pragma once

#include "Crossant/feature/graphics/3d/context.hpp"
#include "Crossant/common/hierarchy.hpp"
#include "Crossant/common/quaternion.hpp"
#include <set>

namespace Crossant::Space {
	using namespace Crossant::Graphics::Graphics3D;

	struct Space;
	struct Object;
	struct Component;

	struct Component : ChildHierarchy<Component, Object> {
		Object &object;

		Component(Object &object) : ChildHierarchy(object), object(object) {}
	};

	struct Object : ChildHierarchy<Object, Space>, ParentHierarchy<Object, Component> {
		Space &space;
		std::set<Component *> &components;

		struct Transform {
			Transform *parent = nullptr;
			Coord3D translation{ 0, 0, 0 };
			Quaternion rotation{ 1, { 0, 0, 0 } };
			Coord3D scalor{ 1, 1, 1 };
			Object &object;

			Transform(Object &object) : object(object) {}

			void Apply() const;
			void ApplyInverse() const;
		};

		Transform transform;

		Object(Space &space) : ChildHierarchy(space), space(space), components(children), transform(*this) {}

		template<std::derived_from<Component> T>
		T *ComponentOf() {
			for(Component *component : children) {
				T *p = dynamic_cast<T *>(component);
				if(p != nullptr)
					return p;
			}
			return nullptr;
		}

		template<std::derived_from<Component> T>
		std::set<T *> ComponentsOf() {
			std::set<T *> components;
			for(Component *component : children) {
				T *p = dynamic_cast<T *>(component);
				if(p != nullptr)
					components.insert((T *)component);
			}
			return components;
		}
	};

	struct Space : Context, ParentHierarchy<Space, Object> {
		std::set<Object *> &objects;

		Space(Crossant::Graphics::Target &target) : Context(target), objects(children) {}

		virtual ~Space() {
			while(!objects.empty())
				delete *objects.begin();
		}

		template<std::derived_from<Component> T>
		std::set<T *> ComponentsOf() {
			std::set<T *> result;
			auto it = result.begin();
			for(Object *object : children) {
				auto components = object->ComponentsOf<T>();
				result.insert(components.begin(), components.end());
			}
			return result;
		}
	};
}