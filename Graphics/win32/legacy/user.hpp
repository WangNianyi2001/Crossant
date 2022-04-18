#pragma once

#include "legacy.hpp"
#include "kernel.hpp"
#include "../../event.hpp"

namespace Graphics::Win32::Legacy {
	struct UserObject : HandledObject {
		UserObject(void *const handle) : HandledObject(handle) {}

		virtual ~UserObject() = default;
	};

	struct ModuleInstance : UserObject {
		ModuleInstance(void *const handle) : UserObject(handle) {}
	};

	struct Menu : UserObject {
		Menu(void *const handle) : UserObject(handle) {}
	};

	struct WindowClass : Object {
		enum struct Style : unsigned long {
			VRedraw = 0x00000001,
			HRedraw = 0x00000002,
			Dblclks = 0x00000008,
			OwnDC = 0x00000020,
			ClassDC = 0x00000040,
			ParentDC = 0x00000080,
			NoClose = 0x00000200,
			SaveBits = 0x00000800,
			ByteAlignClient = 0x00001000,
			ByteAlignWindow = 0x00002000,
			GlobalClass = 0x00004000,
			IME = 0x00010000,
			DropShadow = 0x00020000,
		};

		struct Info {
			Style style = Style::ClassDC;
			void *process = nullptr;
			ModuleInstance *instance = nullptr;
			Icon *icon = nullptr;
			Cursor *cursor = nullptr;
			// Should be a brush
			// Forward declaration doesn't really work here
			HandledObject *brush = nullptr;
			String menuName = String();
			String className = String();
			Icon *smallIcon = nullptr;
		};

		unsigned short const id;
		Info const info;

		WindowClass(unsigned short id, Info info) : id(id), info(info) {}

		static WindowClass *Register(Info info);

		void Unregister();
	};

	struct Window : UserObject {
		struct Event : Graphics::Event<long> {
			unsigned int w = 0U;
			long l = 0L;
		};

		static constexpr int useDefaultCoordinate = 0x80000000;

		enum struct Style : unsigned long {
			Overlapped = 0x00000000L,
			Popup = 0x80000000L,
			Child = 0x40000000L,
			Minimize = 0x20000000L,
			Visible = 0x10000000L,
			Disabled = 0x08000000L,
			ClipSiblings = 0x04000000L,
			ClipChildren = 0x02000000L,
			Maximize = 0x01000000L,
			Border = 0x00800000L,
			DlgFrame = 0x00400000L,
			Caption = Border | DlgFrame,
			VScroll = 0x00200000L,
			HScroll = 0x00100000L,
			SysMenu = 0x00080000L,
			ThickFrame = 0x00040000L,
			Group = 0x00020000L,
			TabStop = 0x00010000L,
			MinimizeBox = 0x00020000L,
			MaximizeBox = 0x00010000L,
			// Common Window Styles
			OverlappedWindow = Overlapped | Caption | SysMenu | ThickFrame | MinimizeBox | MaximizeBox,
			PopupWindow = Popup | Border | SysMenu,
			ChildWindow = Child,
			// Aliases
			Tiled = Overlapped,
			Iconic = Minimize,
			SizeBox = ThickFrame,
			TiledWindow = OverlappedWindow,
		};

		enum struct ExtendedStyle : unsigned long {
			DLGModalFrame = 0x00000001L,
			NoParentNotify = 0x00000004L,
			Topmost = 0x00000008L,
			AcceptFiles = 0x00000010L,
			Transparent = 0x00000020L,
			MDIChild = 0x00000040L,
			ToolWindow = 0x00000080L,
			WindowEdge = 0x00000100L,
			ClientEdge = 0x00000200L,
			ContextHelp = 0x00000400L,
			Right = 0x00001000L,
			Left = 0x00000000L,
			RTLReading = 0x00002000L,
			LTRReading = 0x00000000L,
			LeftScrollBar = 0x00004000L,
			RightScrollBar = 0x00000000L,
			ControlParent = 0x00010000L,
			StaticEdge = 0x00020000L,
			AppWindow = 0x00040000L,
			Layered = 0x00080000,
			NoInheritLayout = 0x00100000L,
			NoRedirectionBitmap = 0x00200000L,
			LayoutRTL = 0x00400000L,
			Composited = 0x02000000L,
			NoActivate = 0x08000000L,
			// Common Window Styles
			OverlappedWindow = WindowEdge | ClientEdge,
			PaletteWindow = WindowEdge | ToolWindow | Topmost,
		};

		struct CreationArguments {
			ExtendedStyle extendedStyle = ExtendedStyle::OverlappedWindow;
			WindowClass *windowClass;
			String windowName = String(L"");
			Style style = Style::OverlappedWindow;
			int x = useDefaultCoordinate;
			int y = useDefaultCoordinate;
			int width = useDefaultCoordinate;
			int height = useDefaultCoordinate;
			Window *parent = nullptr;
			Menu *menu = nullptr;
			ModuleInstance *instance;
		};

		Window(void *const handle) : UserObject(handle) {}

		Window(CreationArguments arguments);

		~Window() override;

		void Run();

		long DefaultProcess(Event event);

		void Quit();
	};
}
