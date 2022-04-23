#pragma once

#include "function.hpp"
#include <concepts>
#include <initializer_list>
#include <algorithm>

namespace Graphics {
	template<typename Component, unsigned dimension>
	struct Vector {
	protected:
		Component components[dimension];

	public:
		// Constructor

		Vector() = default;
		Vector(Vector const &vector) {
			for(unsigned i = 0; i < dimension; ++i)
				components[i] = vector[i];
		}
		template<typename _Component>
		Vector(Vector<_Component, dimension> const &vector) {
			for(unsigned i = 0; i < dimension; ++i)
				components[i] = (Component)vector[i];
		}
		Vector(std::initializer_list<Component> list) {
			unsigned i = 0;
			for(Component component : list) {
				if(i == dimension)
					break;
				components[i] = component;
				++i;
			}
		}

		// Component

		inline Component &operator[](unsigned index) {
			return components[index];
		}
		inline Component operator[](unsigned index) const {
			return components[index];
		}

		// Comparison

		template<
			std::derived_from<BinaryRelation<Component>> Comparator,
			std::derived_from<Folder<bool, Component>> Folder
				= And<bool, Component>
		> static bool Compare(Vector const &a, Vector const &b) {
			Comparator comp = Comparator();
			Folder fold = Folder();
			bool result = fold.unit;
			for(unsigned index = 0; index < dimension; ++index)
				result = fold(result, comp(a[index], b[index]));
			return result;
		}

		inline bool operator==(Vector const &vector) const {
			return Compare<Equal<Component>>(*this, vector);
		}
		inline bool operator!=(Vector const &vector) const {
			return Compare<
				Inequal<Component>,
				Or<bool, Component>
			>(*this, vector);
		}
		inline bool operator<(Vector const &vector) const {
			return Compare<Less<Component>>(*this, vector);
		}
		inline bool operator>(Vector const &vector) const {
			return Compare<Greater<Component>>(*this, vector);
		}
		inline bool operator<=(Vector const &vector) const {
			return Compare<LessEqual<Component>>(*this, vector);
		}
		inline bool operator>=(Vector const &vector) const {
			return Compare<GreaterEqual<Component>>(*this, vector);
		}

		// Arithmetic

		template<std::derived_from<BinaryOperator<Component>> Operator>
		static Vector Arithmetic(Vector const &a, Vector const &b) {
			Operator op{};
			Vector res;
			for(unsigned i = 0; i < dimension; ++i)
				res[i] = op(a[i], b[i]);
			return res;
		}

		inline Vector operator+(Vector const &vector) const {
			return Arithmetic<Plus<Component>>(*this, vector);
		}
		inline Vector operator-(Vector const &vector) const {
			return Arithmetic<Minus<Component>>(*this, vector);
		}
	};
}
