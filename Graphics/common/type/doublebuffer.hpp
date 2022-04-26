#pragma once

namespace Graphics {
	template<typename T>
	struct DoubleBuffer {
		T front, back;

		DoubleBuffer(T const &front = T{}, T const &back = T{}) :
			front(front), back(back) {}

		T Swap() {
			T temp = back;
			back = front;
			front = temp;
			return temp;
		}

		T Push(T incoming) {
			T retired = back;
			back = front;
			front = incoming;
			return retired;
		}
	};
}
