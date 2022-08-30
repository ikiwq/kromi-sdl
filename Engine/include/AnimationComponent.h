#pragma once

#include "ECS.h"

class Timer;
class FixedSpriteComponent;

class AnimationComponent : public Component {
public:
	int offsetX, offsetY;
	int frameCount;
private:
	Timer* timer;
	FixedSpriteComponent* Sprite;
	int frameW, frameH, spacingX, spacingY;
	float AccumdT, animationDuration;

	bool canAnimate;
public:
	AnimationComponent(int fW, int fH, int fC, float aDuration);

	~AnimationComponent();

	bool Init() override;

	void Update() override;
};