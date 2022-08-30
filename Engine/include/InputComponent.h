#pragma once

#include "ECS.h"
#include "Maths.h"
#include <string.h>

class InputComponent : public Component {
public:
	enum MOUSE_BUTTON {
		left = 0,
		right,
		middle,
		back,
		forward
	};

	
private:
	Uint8* PreviousKeyboardState;
	const Uint8* CurrentKeyboardState;
	int numkeys;

	Uint32 PreviousMouseState;
	Uint32 CurrentMouseState;

	int mousex, mousey;
public:
	InputComponent();
	~InputComponent();

	bool isKeyDown(SDL_Scancode scancode);
	bool KeyPress(SDL_Scancode scancode);
	bool KeyRelease(SDL_Scancode scancode);

	bool isMouseButtonDown(MOUSE_BUTTON button);
	bool ButtonPress(MOUSE_BUTTON button);
	bool ButtonRelease(MOUSE_BUTTON button);

	Vector2 GetMousePos();

	void UpdateCurrInput();
	void UpdatePrevInput();
};