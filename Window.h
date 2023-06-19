#pragma once

#include "Windows.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

class Window
{
public:
	Window(const wchar_t*, int, int);
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void startWindow();

	void (*paint)(HWND, UINT, WPARAM, LPARAM);
	void (*command)(HWND, UINT, WPARAM, LPARAM);

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};