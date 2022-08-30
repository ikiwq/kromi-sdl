#pragma once

#include "ECS.h"

class InputComponent;

class ButtonScript : public Component {
public:
	InputComponent* Input;
	
	ButtonScript() = default;
	~ButtonScript();

	bool Init() override;

	void Update() override;
};