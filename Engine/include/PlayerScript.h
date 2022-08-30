#pragma once

#include "ECS.h"

class Transform2D;
class FixedSpriteComponent;
class AnimationComponent;
class InputComponent;
class Timer;

class PlayerScript : public Component {
private:
	Transform2D* Transform;
	FixedSpriteComponent* Sprite;
	AnimationComponent* Animation;
	InputComponent* Input;
	Timer* Timer;

	bool facingRight;
	bool isAnimating;

	bool isStanding;
	bool isRunning;
	bool isAttacking;

public:
	PlayerScript();

	~PlayerScript();

	bool Init() override;

	void Update() override;
};