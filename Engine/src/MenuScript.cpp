#include "MenuScript.h"
#include "MainMenu.h"

MenuScript::MenuScript(MainMenu* ownerMenu_) {
	ownerMenu = ownerMenu_;
}

bool MenuScript::Init() {
	if (!owner->hasComponent<InputComponent>()) {
		std::cout << "Entity must have Input component!" << std::endl;
		return false;
	}
	
	Input = &owner->getComponent<InputComponent>();

	mouseRect.x = 0;
	mouseRect.y = 0;
	mouseRect.w = 2;
	mouseRect.h = 2;
}

void MenuScript::Update() {
	Input->UpdateCurrInput();

	mouseRect.x = Input->GetMousePos().x;
	mouseRect.y = Input->GetMousePos().y;

	if (Collisions::AxisCollision(mouseRect,
		ownerMenu->Button1.getComponent<FixedSpriteComponent>().GetDestRect())) {
		ownerMenu->Button1.getComponent<FixedSpriteComponent>().red = 150;
		if (Input->ButtonPress(Input->left)) {
			ownerMenu->isActive = false;
		}
	}
	else {
		ownerMenu->Button1.getComponent<FixedSpriteComponent>().red = 50;
	}

	if (Collisions::AxisCollision(mouseRect,
		ownerMenu->Button2.getComponent<FixedSpriteComponent>().GetDestRect())) {
		ownerMenu->Button2.getComponent<FixedSpriteComponent>().red = 150;
		if (Input->ButtonPress(Input->left)) {
			ownerMenu->ShouldQuit = true;
		}
	}else {
		ownerMenu->Button2.getComponent<FixedSpriteComponent>().red = 50;
	}

	

	Input->UpdatePrevInput();
}