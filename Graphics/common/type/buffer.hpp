#pragma once

#include <optional>
#include <concepts>

namespace Graphics {
template<typename T>
	struct SingleBuffer {
	protected:
		std::optional<T> data;

		virtual void Set(T &value) {}

		virtual void Remove(T &value) {}

	public:

		SingleBuffer() : data(false) {}
		SingleBuffer(T const &value) : data(value) {}

		std::optional<T> Get() {
			return data;
		}

		std::optional<T> Empty() {
			if(data.has_value())
				Remove(data.value());
			data = std::optional<T>();
		}

		std::optional<T> Replace(std::optional<T> const &newData) {
			auto old = Empty();
			if(newData.has_value())
				Set(newData.value());
			data = newData;
			return old;
		}

		std::optional<T> Replace(T const &value) {
			return Replace(std::optional<T>(value));
		}
	};

	template<typename T, std::derived_from<SingleBuffer<T>> Buffer = SingleBuffer<T>>
	struct DoubleBuffer {
		Buffer front, back;

		DoubleBuffer() = default;
		DoubleBuffer(T const &front, T const &back = T{}) :
			front(front), back(back) {}

		void Swap() {
			auto temp = back.Get();
			back.Replace(front.Get());
			front.Replace(temp);
		}

		T Push(T const &newValue) {
			auto old = back.Replace(front.Get());
			front.Replace(newValue);
			return old;
		}
	};
}
