#pragma once

#include "ECS.h"

class InputComponent;

class EnemyScript : public Component {
public:
	int health;
	InputComponent* Input;

	EnemyScript():health (100) {
		
	}
	~EnemyScript() = default;

	bool Init() override {
		Input = &owner->getComponent<InputComponent>();
		return true;
	}
	void Update() override {
		if(health<=0){
			owner->Kill();
		}
	}
	
};