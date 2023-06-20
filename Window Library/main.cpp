#include "Window.h"
#include <iostream>

Window window = Window(L"Demo Window", 700, 300);

void buttonAction(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MessageBox(0, L"Demo Button Action", L"Button Action", MB_OK);
	window.stop();
}

void Paint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	createLabel(L"Demo Label", 20, 10, 90, 20, 1, hWnd);
	createButton(L"Demo Button", 20, 60, 90, 20, 2, hWnd);
	createTextField(L"", 20, 110, 90, 20, 3, hWnd);
}
void Command(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	assignActionID(2, hWnd, uMsg, wParam, lParam, buttonAction);
}

int main() {
	window.paint = Paint;
	window.command = Command;

	window.start();

	int input;
	std::cin >> input;

	return 0;
}