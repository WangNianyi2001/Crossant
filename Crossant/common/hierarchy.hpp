#pragma once

#include <set>

namespace Crossant {
	template<typename Self>
	struct Hierarchy {
		virtual ~Hierarchy() {}
	};

	template<typename Self, typename Parent>
	struct ChildHierarchy : Hierarchy<Self> {
		Parent &parent;

		ChildHierarchy(Parent &parent) : parent(parent) {
			parent.children.insert((Self *)this);
		}

		virtual ~ChildHierarchy() {
			if(parent.children.contains((Self *)this))
				parent.children.erase((Self *)this);
		}
	};

	template<typename Self, typename Child>
	struct ParentHierarchy : Hierarchy<Self> {
		std::set<Child *> children;

		virtual ~ParentHierarchy() {
			while(!children.empty())
				delete *children.begin();
		}
	};
}