#include "Window.h"

Window* window;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_PAINT:
		window->paint(hWnd, uMsg, wParam, lParam);
		break;
	case WM_COMMAND:
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

void paintPlaceHolder(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MessageBox(0, L"Unititialized Create Function", L"Error", MB_OK | MB_ICONWARNING);
}
void commandPlaceHolder(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MessageBox(0, L"Unititialized Command Function", L"Error", MB_OK | MB_ICONWARNING);
}

Window::Window(const wchar_t* title, int width, int height)
	: m_hInstance(GetModuleHandle(nullptr)) 
{
	window = this;
	
	if (!this->paint) {
		this->paint = paintPlaceHolder;
	}
	if (!this->command) {
		this->command = commandPlaceHolder;
	}

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
	bool isRunning = true;

	while (isRunning) {
		if (!this->ProcessMessages()) {
			isRunning = false;
		}
		//render
	}
	delete this;
}