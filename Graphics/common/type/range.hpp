#pragma once

namespace Graphics {
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
			Min<Point const &> const minOp{};
			Max<Point const &> const maxOp{};
			for(; it != list.end(); ++it) {
				min = minOp(min, *it);
				max = maxOp(max, *it);
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
