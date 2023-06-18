#pragma once

#include "Windows.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window(const wchar_t* title, int width, int height);
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();

	bool ProcessMessages();

	bool isRunning;

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};

void startWindow(Window* win);