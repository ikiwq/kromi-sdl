#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <bitset>
#include <array>

#include "Scene.h"

class Component;
class Entity;

using ComponentID = unsigned int;
using Group = unsigned int;

constexpr unsigned int MAX_COMPONENTS = 32;
constexpr unsigned int MAX_GROUPS = 32;

using ComponentsSignature = std::bitset<MAX_COMPONENTS>;
using GroupSignature = std::bitset<MAX_GROUPS>;

using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

enum groupLabels : unsigned int {
	zerolayer,
	firstlayer,
	secondlayer,
	thirdlayer
};

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentID getComponentID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

class Component {
public:
	Entity* owner;

	virtual bool Init() { return true; }
	virtual void Update() {}
	virtual void Render() {}

	Component() = default;
	virtual ~Component() {}
};

class Entity {
public:
	Scene* EntityScene;

	Entity(Scene* scene) {
		EntityScene = scene;
	}

	~Entity() {
		componentsList.clear();
		EntityScene = nullptr;
	}

private:
	bool Active = true;
	std::vector<std::unique_ptr<Component>> componentsList;

	ComponentArray componentArray;
	ComponentsSignature componentSignature;
	GroupSignature groupSignature;

public:

	void Update() {
		for (auto& component : componentsList) {
			component->Update();
		}
	}

	void Render() {
		for (auto& component : componentsList) {
			component->Render();
		}
	}

	bool isActive() const { return Active; }

	bool HasGroup(Group group) {
		return groupSignature[group];
	}
	
	void AddGroup(Group group);

	void DelGroup(Group group) {
		groupSignature[group] = false;
	}

	void Kill() { Active = false; }

	template<typename T> bool hasComponent() const {
		return componentSignature[getComponentID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) {
		T* cmpnt(new T(std::forward<TArgs>(args)...));
		cmpnt->owner = this;

		if (cmpnt->Init()) {
			std::unique_ptr<Component> uPtr{ cmpnt };
			componentsList.emplace_back(std::move(uPtr));

			componentArray[getComponentID<T>()] = cmpnt;
			componentSignature[getComponentID<T>()] = true;
		}
		else {
			delete cmpnt;
			return *cmpnt;
		}
		
		return *cmpnt;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class EntityManager {
public:
	Scene* ManagerScene;
	std::array<std::vector<Entity*>, MAX_GROUPS> groupEntities;
private:
	std::vector<std::unique_ptr<Entity>> entities;
public:

	EntityManager() = default;

	~EntityManager() {
		ManagerScene = nullptr;

		for (int i = 0; i < MAX_GROUPS; i++) {
			auto& v(groupEntities[i]);
			v.clear();
		}

		entities.clear();
	}

	void Update() {
		for (int i = 0; i < MAX_GROUPS; i++) {
			for (auto& entity : groupEntities[i]) {
				entity->Update();
			}
		}
	}

	void Render() {
		
		for (int i=0; i < MAX_GROUPS; i++) {
			for (auto& entity : groupEntities[i]) {
				entity->Render();
			}
		}
	}

	void Refresh() {
		for (int i = 1; i < MAX_GROUPS; i++) {
			auto& v(groupEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* ent) {
						return !ent->isActive() || !ent->HasGroup(i); }), std::end(v));
		}
	}

	void AddToGroup(Entity* ent, Group group) {
		groupEntities[group].emplace_back(ent);
	}

	std::vector<Entity*>& getGroup(Group group) {
		return groupEntities[group];
	}

	Entity& addEntity() {
		Entity* ent = new Entity(ManagerScene);
		std::unique_ptr<Entity> uPtr{ ent };
		entities.emplace_back(std::move(uPtr));
		return *ent;
	}

};
