#include "Window.h"

void Paint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//add button to window
	CreateWindow(L"button", L"demo text",
		WS_VISIBLE | WS_CHILD,
		20, 90, 190, 25,
		hWnd, (HMENU)1, NULL, NULL);
}

void Command(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (LOWORD(wParam)) {
		//button action
	case 1:
		MessageBox(0, L"Button Pressed", L"Demo", MB_OK);
		break;
	}
}

int main() {
	Window* window = new Window(L"Demo Window", 700, 300);

	window->paint = Paint;
	window->command = Command;

	window->startWindow();

	return 0;
}