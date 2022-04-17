#pragma once
#include "../event.hpp"

namespace Graphics {
	namespace Win32 {
		struct WindowEvent : Event<long> {
			unsigned int w;
			long l;
		};

		class Window : public EventDistributor<long, WindowEvent> {
		protected:
			inline static Window *main = nullptr;

			struct Impl;
			Impl *impl = nullptr;

			Window() = default;

		public:
			static bool Created() {
				return main != nullptr;
			}
			static Window *Get() {
				return main;
			}
			static Window *Create();

			virtual void Miss(WindowEvent event) override;

			void Run();
			void Stop();
		};

		extern void Main();
	}
}
