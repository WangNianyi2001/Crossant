#pragma once

namespace Graphics {
	template<typename T>
	struct Just {
	protected:
		T value;

	public:
		Just() : value(T{}) {}
		Just(T const &value) : value(value) {}
		virtual ~Just() = default;

		operator T &() {
			return value;
		}
	};
}
