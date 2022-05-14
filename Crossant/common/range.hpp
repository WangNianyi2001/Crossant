#pragma once

#include "function.hpp"

namespace Crossant {
	template<typename Point>
	struct Range {
		virtual bool Contains(Point const &point) const = 0;
	};

	template<typename Point>
	struct BoxRange : Range<Point> {
		Point min, max;

		BoxRange(Point const &min, Point const &max) : min(min), max(max) {}
#pragma warning(suppress: 26495)
		BoxRange(std::initializer_list<Point const> list) {
			if(list.size() == 0)
				return;
			auto it = list.begin();
			min = max = *it;
			for(; it != list.end(); ++it) {
				min = Operator::min<Point>(min, *it);
				max = Operator::max<Point>(max, *it);
			}
		}

		virtual bool Contains(Point const &point) const override {
			return point >= min && point < max;	// Left-close right-open
		}

		Point Diagonal() const {
			return max - min;
		}
	};
}
