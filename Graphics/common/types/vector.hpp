#pragma once

#include "function.hpp"
#include <concepts>
#include <initializer_list>
#include <algorithm>

namespace Graphics {
	template<typename Component, int dimension>
	struct Vector {
	protected:
		Component components[dimension];

	public:
		Vector(std::initializer_list<Component> list) {
			size_t i = 0;
			for(Component component : list) {
				if(i == dimension)
					break;
				components[i] = component;
				++i;
			}
		}

		inline Component &operator[](unsigned index) {
			return components[index];
		}

		inline Component operator[](unsigned index) const {
			return components[index];
		}

		using ComponentComparator = Comparator<Component>;

		template<
			std::derived_from<Comparator<Component>> _Comparator,
			std::derived_from<BooleanOperation> _Folder
		> static bool Compare(
			Vector<Component, dimension> const &a,
			Vector<Component, dimension> const &b
		) {
			_Comparator comp = _Comparator();
			_Folder fold = _Folder();
			bool result = fold.unit;
			for(unsigned index = 0; index < dimension; ++index)
				result = fold(result, comp(a[index], b[index]));
			return result;
		}

		bool operator==(Vector const &vector) const {
			return Compare<Comparator<Component>::Equal, BooleanOperation::And>(*this, vector);
		}
		bool operator<(Vector const &vector) const {
			return Compare<Comparator<Component>::Less, BooleanOperation::And>(*this, vector);
		}
		bool operator>(Vector const &vector) const {
			return Compare<Comparator<Component>::Greater, BooleanOperation::And>(*this, vector);
		}
		bool operator!=(Vector const &vector) const {
			return !operator==(vector);
		}
		bool operator<=(Vector const &vector) const {
			return operator<(vector) || operator==(vector);
		}
		bool operator>=(Vector const &vector) const {
			return operator>(vector) || operator==(vector);
		}
	};
}
