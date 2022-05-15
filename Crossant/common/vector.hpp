#pragma once

#include <functional>
#include <concepts>
#include <initializer_list>
#include <algorithm>
#include <cmath>

namespace Crossant {
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
		template<typename From, unsigned d>
		Vector(Vector<From, d> const &vector) {
			unsigned i = 0, lim = std::min(dimension, d);
			for(; i < lim; ++i)
				components[i] = (Component)vector[i];
			for(; i < dimension; ++i)
				components[i] = (Component)0;
		}
#pragma warning(suppress: 26495)
		Vector(std::initializer_list<Component> list) {
			unsigned i = 0;
			for(Component component : list) {
				if(i == dimension)
					break;
				components[i] = component;
				++i;
			}
			for(; i < dimension; ++i)
				components[i] = (Component)0;
		}

		// Component

		inline Component &operator[](unsigned index) {
			return components[index];
		}
		inline Component operator[](unsigned index) const {
			return components[index];
		}

		// General operation

		template<typename To = Component>
		Vector<To, dimension> Operate(std::function<To(Component)> const &op) const {
			Vector<To, dimension> result;
			for(unsigned i = 0; i < dimension; ++i)
				result[i] = op(operator[](i));
			return result;
		}
		template<typename To = Component, typename With = Component>
		Vector<To, dimension> Operate(std::function<To(Component, With)> const &op, Vector<With, dimension> const &v) const {
			Vector<To, dimension> result;
			for(unsigned i = 0; i < dimension; ++i)
				result[i] = op(operator[](i), v[i]);
			return result;
		}
		template<typename To = Component>
		inline Vector<To, dimension> Operate(std::function<To(Component, Component)> const &op, Vector const &v) const {
			return Operate<To, Component>(op, v);
		}
		inline Vector Operate(std::function<Component(Component, Component)> const &op, Vector const &v) const {
			return Operate<Component, Component>(op, v);
		}
		template<typename To = Component, typename With = Component>
		Vector<To, dimension> Operate(std::function<To(Component, With)> const &op, With const &with) const {
			Vector<To, dimension> result;
			for(unsigned i = 0; i < dimension; ++i)
				result[i] = op(operator[](i), with);
			return result;
		}

		template<typename Ret = Component>
		Ret Fold(std::function<Ret(Component, Component)> const &fold, Ret unit) const {
			for(unsigned i = 0; i < dimension; ++i)
				unit = fold(unit, operator[](i));
			return unit;
		}

		// Attribute

		inline Component SquaredModule() const {
			return Operate(Operator::square<Component>).Fold<Component>(Operator::plus<Component>, 0);
		}
		inline Component Module() const {
			return std::sqrt(SquaredModule());
		}

		// Arithmetic

		inline Vector operator+(Vector const &v) const {
			return Operate(Operator::plus<Component>, v);
		}
		inline Vector operator-(Vector const &v) const {
			return Operate(Operator::minus<Component>, v);
		}
		inline Vector operator*(Component s) const {
			return Operate(Operator::multiply<Component>, s);
		}
		inline Vector operator/(Component s) const {
			return Operate(Operator::divide<Component>, s);
		}
		inline Vector operator*(Vector const &v) const {
			return Operate(Operator::multiply<Component>, v);
		}
		inline Vector operator/(Vector const &v) const {
			return Operate(Operator::divide<Component>, v);
		}
		inline Vector Min(Vector const &v) const {
			return Operate(Operator::min<Component>, v);
		}
		inline Vector Max(Vector const &v) const {
			return Operate(Operator::max<Component>, v);
		}
		inline Vector Inverse() const {
			return Operate(Operator::inverse<Component>);
		}

		// Comparison

		bool Compare(
			std::function<bool(Component, Component)> const &op,
			std::function<bool(bool, bool)> const &folder,
			Vector const &v, bool unit = true
		) const {
			return Operate<bool, Component>(op, v).Fold<bool>(folder, unit);
		}

		inline bool operator==(Vector const &v) const {
			return Compare(Operator::equal<Component>, Operator::logicAnd, v);
		}
		inline bool operator!=(Vector const &v) const {
			return Compare(Operator::inequal<Component>, Operator::logicOr, v);
		}
		inline bool operator<(Vector const &v) const {
			return Compare(Operator::less<Component>, Operator::logicAnd, v);
		}
		inline bool operator>(Vector const &v) const {
			return Compare(Operator::greater<Component>, Operator::logicAnd, v);
		}
		inline bool operator<=(Vector const &v) const {
			return Compare(Operator::lessEqual<Component>, Operator::logicAnd, v);
		}
		inline bool operator>=(Vector const &v) const {
			return Compare(Operator::greaterEqual<Component>, Operator::logicAnd, v);
		}
	};
}