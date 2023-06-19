# Window
I'm learning, don't make fun of me

```cpp
#include "windows.h"
#include "Window.h"

void Paint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  //add button to window
  CreateWindow(L"button", L"button text",
	WS_VISIBLE | WS_CHILD,
	10, 90, 190, 25,
	hWnd, (HMENU)1, NULL, NULL);
}

void Command(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (LOWORD(wParam)) {
    //button action
    case 1:
      MessageBox(0, "Button Pressed", L"Pressed", MB_OK);
      break;
  }
}

int main(){
  Window* window = new Window(L"Demo Window", 700, 300);
  
  window->paint = Paint; //initialize window's paint method
  window->command = Command; //initialize window's command method
  
  startWindow(window);
}
```
