#include "AnimationComponent.h"

#include "Timer.h"
#include "FixedSpriteComponent.h"

//The animation components moves the source rectangle, giving the illusion of the sprite moving.

//You need to specify how big is a single frame in width and height, how many frames an animation has
//and the duration of them.
AnimationComponent::AnimationComponent(int fW, int fH, int fC, float aDuration) :
	spacingX(0), spacingY(0), offsetX(0), offsetY(0), AccumdT(0), canAnimate(true) {
	timer = Timer::GetInstance();
	frameW = fW;
	frameH = fH;

	frameCount = fC;
	animationDuration = aDuration;
}

AnimationComponent::~AnimationComponent() {
	timer = nullptr;
	Sprite = nullptr;
}

bool AnimationComponent::Init() {
	//Dependencies
	if (!owner->hasComponent<FixedSpriteComponent>()) {
		std::cout << "Entity must have Fixed Sprite Component!" << std::endl;
		return false;
	}
	if (owner->hasComponent<AnimationComponent>()) {
		std::cout << "Entity has already got Animation Component!";
		return false;
	}
	Sprite = &owner->getComponent<FixedSpriteComponent>();
	Sprite->HasAnimation = true;

	//In the init function, the source Rects takes the offset position and the frame sizes.
	//The offset position is useful if you have multiple sprites types(running, jumping)
	//across the y axis or the sprite has a spacing with the border of the image.
	Sprite->srcRect.x = offsetX;
	Sprite->srcRect.y = offsetY;
	Sprite->srcRect.w = frameW;
	Sprite->srcRect.h = frameH;
	return true;
}

void AnimationComponent::Update() {
	//the animation is like a render loop: it accumulates the delta time and once it is more
	//than the animation of a single frames, goes into the next one.
	if (canAnimate) {
		AccumdT += timer->GetPhysicsDt();
		if (AccumdT > animationDuration) {
			if (Sprite->srcRect.x < (spacingX + frameW) * (frameCount - 2)) {
				Sprite->srcRect.x += spacingX + frameW;
			}
			//if we are going out of the texture X axis, we reset
			else {
				Sprite->srcRect.x = 0;
			}
			//and we reset the timer at each frame call
			AccumdT = 0;
		}
	}
}