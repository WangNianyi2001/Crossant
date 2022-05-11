#pragma once

#include <optional>
#include <concepts>

namespace Crossant {
template<typename T>
	struct SingleBuffer {
	protected:
		std::optional<T> data;

	public:
		SingleBuffer() : data() {}
		SingleBuffer(T const &value) : data(value) {}

		bool HasValue() {
			return data.has_value();
		}

		std::optional<T> &Get() {
			return data;
		}

		std::optional<T> Empty() {
			auto old = data;
			data = std::optional<T>();
			return old;
		}

		std::optional<T> Replace(std::optional<T> const &newData) {
			auto old = Empty();
			data = newData;
			return old;
		}

		std::optional<T> Replace(T const &value) {
			return Replace(std::optional<T>(value));
		}
	};

	template<typename T>
	struct DoubleBuffer {
		SingleBuffer<T> front, back;

		DoubleBuffer() = default;
		DoubleBuffer(T const &front, T const &back = T{}) :
			front(front), back(back) {}

		bool HasValue() {
			return front.HasValue();
		}

		std::optional<T> &Get() {
			return front.Get();
		}

		virtual void Swap() {
			auto temp = back.Get();
			back.Replace(front.Get());
			front.Replace(temp);
		}

		virtual std::optional<T> Push(T const &newValue) {
			auto old = back.Replace(front.Get());
			front.Replace(newValue);
			return old;
		}
	};
}
