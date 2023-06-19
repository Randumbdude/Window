# Window (winAPI)
I'm learning, don't make fun of me

I know its bad but it works

### Example: (main.cpp)
```cpp
#include "Window.h"

void demoButtonAction(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  MessageBox(0, L"Demo Button Action", L"Button Action", MB_OK);
}

void Paint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  createLabel(L"Demo Label", 20, 10, 90, 20, 1, hWnd);
  createButton(L"Demo Button", 20, 60, 90, 20, 2, hWnd);
  createTextField(L"", 20, 110, 90, 20, 3, hWnd);
}

void Command(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  assignActionID(2, hWnd, uMsg, wParam, lParam, demoButtonAction); //assigning the 'demoButtonAction' method to the button's actionID
}

int main(){
  Window* window = new Window(L"Demo Window", 700, 300);
  
  window->paint = Paint; //initialize window's paint method
  window->command = Command; //initialize window's command method
  
  startWindow(window);

  return 0;
}
```
