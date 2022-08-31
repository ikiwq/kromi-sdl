#include "InputComponent.h"
#include "SDL.h"

//The input component manages all the inputs.

InputComponent::InputComponent() {
	CurrentKeyboardState = SDL_GetKeyboardState(&numkeys);
	PreviousKeyboardState = new Uint8[numkeys];
	memcpy(PreviousKeyboardState, CurrentKeyboardState, numkeys);
}

InputComponent::~InputComponent() {
	delete[] PreviousKeyboardState;
	PreviousKeyboardState = nullptr;
}

bool InputComponent::isKeyDown(SDL_Scancode scancode) {
	return CurrentKeyboardState[scancode];
}

bool InputComponent::KeyPress(SDL_Scancode scancode) {
	return !PreviousKeyboardState[scancode] && CurrentKeyboardState[scancode];
}

bool InputComponent::KeyRelease(SDL_Scancode scancode) {
	return PreviousKeyboardState[scancode] && !CurrentKeyboardState[scancode];
}

bool InputComponent::isMouseButtonDown(MOUSE_BUTTON button) {
	Uint32 mask = 0;
	if (button == 0) {
		mask = SDL_BUTTON_LMASK;
	}
	else if (button == 1) {
		mask = SDL_BUTTON_RMASK;
	}
	else if (button == 2) {
		mask = SDL_BUTTON_MMASK;
	}
	return (CurrentMouseState &mask);
}

bool InputComponent::ButtonPress(MOUSE_BUTTON button) {
	Uint32 mask = 0;
	if (button == 0) {
		mask = SDL_BUTTON_LMASK;
	}
	else if (button == 1) {
		mask = SDL_BUTTON_RMASK;
	}
	else if (button == 2) {
		mask = SDL_BUTTON_MMASK;
	}
	return !(PreviousMouseState & mask) && (CurrentMouseState & mask);
}

bool InputComponent::ButtonRelease(MOUSE_BUTTON button) {
	Uint32 mask = 0;
	if (button == 0) {
		mask = SDL_BUTTON_LMASK;
	}
	else if (button == 1) {
		mask = SDL_BUTTON_RMASK;
	}
	else if (button == 2) {
		mask = SDL_BUTTON_MMASK;
	}
	return (PreviousMouseState & mask) && !(CurrentMouseState & mask);
}

Vector2 InputComponent::GetMousePos() {
	return Vector2(mousex, mousey);
}
void InputComponent::UpdateCurrInput() {
	CurrentKeyboardState = SDL_GetKeyboardState(NULL);
	CurrentMouseState = SDL_GetMouseState(&mousex, &mousey);
}

void InputComponent::UpdatePrevInput() {
	memcpy(PreviousKeyboardState, CurrentKeyboardState, numkeys);
	PreviousMouseState = CurrentMouseState;
}