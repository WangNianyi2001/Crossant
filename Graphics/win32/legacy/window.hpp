#pragma once

#include "user.hpp"

namespace Graphics::Win32::Legacy {
	struct Window : UserObject {
		using Message = unsigned int;
		using W = unsigned __int64;
		using L = __int64;

		struct Event : Graphics::Event<Message> {
			W w = 0;
			L l = 0;

			Event(Message type, W w, L l) :
				Graphics::Event<Message>(type),
				w(w), l(l) {}
		};

		static constexpr int useDefaultCoordinate = 0x80000000;

		Window(void *const handle) : UserObject(handle) {}

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
		Window(CreationArguments arguments);

		~Window() override;

		bool ProcessEvent(Message min = 0, Message max = 0);
		L DefProc(Event event);

		enum struct ShowState : char {
			Hide = 0,
			Shownormal = 1,
			Normal = 1,
			Showminimized = 2,
			Showmaximized = 3,
			Maximize = 3,
			Shownoactivate = 4,
			SetShowState = 5,
			Minimize = 6,
			Showminnoactive = 7,
			Showna = 8,
			Restore = 9,
			Showdefault = 10,
			Forceminimize = 11,
			Max = 11,
		};
		void SetShowState(ShowState state);

		void UpdateClient();
		void ValidateClient();
	};
}