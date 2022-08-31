#pragma once

#include "ECS.h"
#include "InputComponent.h"

class MainMenu;

class MenuScript : public Component {
public:
	MainMenu* ownerMenu;
	InputComponent* Input;
	SDL_Rect mouseRect;
	MenuScript(MainMenu* ownerMenu_);
	~MenuScript() = default;

	bool Init() override;

	void Update() override;


};