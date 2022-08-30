#include "ButtonScript.h"
#include "InputComponent.h"
#include "Collisions.h"

ButtonScript::~ButtonScript() {
	Input = nullptr;
}

bool ButtonScript::Init() {
	if (!owner->hasComponent<InputComponent>()) {
		std::cout << "Entity must have input component!" << std::endl;
		return false;
	}
	Input = &owner->getComponent<InputComponent>();

	return true;
}

void ButtonScript::Update() {
	Input->UpdateCurrInput();
	if (Input->ButtonPress(Input->right) ) {

	}
	if (Input->ButtonPress(Input->left)) {

	}
	Input->UpdatePrevInput();
}