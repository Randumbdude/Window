#include "Window.h"

Window* window;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_PAINT:
		if (!window->paint) break;
		window->paint(hWnd, uMsg, wParam, lParam);
		break;
	case WM_COMMAND:
		if (!window->command) break;
		window->command(hWnd, uMsg, wParam, lParam);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void createButton(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd)
{
	CreateWindow(L"button", text, WS_VISIBLE | WS_CHILD, x, y, width, height, hWnd, (HMENU)actionID, NULL, NULL);
}

void createLabel(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd) {
	CreateWindow(L"static", text, WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hWnd, (HMENU)actionID, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
}

void createTextField(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd) {
	CreateWindow(L"edit", text, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER, x, y, width, height, hWnd, (HMENU)actionID, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
}

void assignActionID(int actionID, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void (*action)(HWND, UINT, WPARAM, LPARAM)) {
	if (LOWORD(wParam) == actionID) {
		action(hWnd, uMsg, wParam, lParam);
	}
}

Window::Window(const wchar_t* title, int width, int height)
	: m_hInstance(GetModuleHandle(nullptr))
{
	window = this;

	const wchar_t* CLASS_NAME = L"Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc; // Fix later

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, true);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		title,
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
	const wchar_t* CLASS_NAME = L"Window Class";

	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages() {
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return true;
}

void Window::startWindow()
{
	this->isRunning = true;

	while (this->isRunning) {
		if (!this->ProcessMessages()) {
			this->isRunning = false;
		}
		//render
	}
	delete this;
}
void Window::stopWindow() {
	this->isRunning = false;
}