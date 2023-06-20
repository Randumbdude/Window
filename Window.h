#pragma once

#include "Windows.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void createButton(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd);
void createLabel(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd);
void createTextField(const wchar_t* text, int x, int y, int width, int height, int actionID, HWND hWnd);

void assignActionID(int actionID, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void (*action)(HWND, UINT, WPARAM, LPARAM));

class Window
{
public:
	Window(const wchar_t* title, int width, int height);
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void startWindow();
	void stopWindow();

	bool isRunning;

	void (*paint)(HWND, UINT, WPARAM, LPARAM);
	void (*command)(HWND, UINT, WPARAM, LPARAM);

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};