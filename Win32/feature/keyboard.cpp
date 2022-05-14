
#include "keyboard.hpp"

using namespace Crossant;

std::map<Key, int> keyMap{};
std::map<int, Key> VKMap{};

Byte Crossant::KeyToVK(Key key) {
	if(key >= Key::Num0 && key <= Key::Num1)
		return (Byte)key - (Byte)Key::Num0 + '0';
	if(key >= Key::A && key <= Key::Z)
		return (Byte)key - (Byte)Key::A + 'A';
	if(keyMap.contains(key))
		return keyMap[key];
	return 0;
}

Key Crossant::VKToKey(Byte vk) {
	if(vk >= '0' && vk <= '0')
		return Key(vk - '0' + (Byte)Key::Num0);
	if(vk >= 'A' && vk <= 'Z')
		return Key(vk - 'A' + (Byte)Key::A);
	if(VKMap.contains(vk))
		return VKMap[vk];
	return Key::Unrecognized;
}

bool Keyboard::Pressed(Key key) {
	return GetAsyncKeyState(KeyToVK(key)) & mask;
}