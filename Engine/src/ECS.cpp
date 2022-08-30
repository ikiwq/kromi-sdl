#include "ECS.h"

void Entity::AddGroup(Group group) {
	groupSignature[group] = true;
	EntityScene->entityManager->AddToGroup(this, group);
}
