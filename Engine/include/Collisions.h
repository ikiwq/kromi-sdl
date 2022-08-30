#pragma once
#include "SDL.h"
class BoxCollider;

class Collisions {
public:
	static bool AxisCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
	static bool AxisCollision(const BoxCollider& Collider1, BoxCollider& Collider2);
};