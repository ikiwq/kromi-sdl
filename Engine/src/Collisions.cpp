#include "Collisions.h"
#include "BoxCollider.h"

bool Collisions::AxisCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	if (
		rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y
		) {
		return true;
	}
	return false;
}

bool Collisions::AxisCollision(const BoxCollider& Collider1, BoxCollider& Collider2) {
	if (Collider1.tag == Collider2.tag) {
		return false;
	}

	if (AxisCollision(Collider1.BoxColliderRect, Collider2.BoxColliderRect)) {
		std::cout << Collider1.tag << "hit" << Collider2.tag << std::endl;
		return true;
	}

	return false;
}