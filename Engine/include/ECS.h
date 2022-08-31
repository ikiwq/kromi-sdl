#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <bitset>
#include <array>

#include "Scene.h"

//The Entity Component System can assign attributes to an entity and then group them.

class Component;
class Entity;

using ComponentID = unsigned int;
using Group = unsigned int;

constexpr unsigned int MAX_COMPONENTS = 32;
constexpr unsigned int MAX_GROUPS = 32;

//We can track Entity attributes (such as components and groups) using a bitmask
using ComponentsSignature = std::bitset<MAX_COMPONENTS>;
using GroupSignature = std::bitset<MAX_GROUPS>;

//This is the array where the entity components are stored in
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

enum groupLabels : unsigned int {
	zerolayer, //layer for the map
	firstlayer, //layer for map details
	secondlayer, //layer for collision tile
	thirdlayer,//layer for player and entities
	fourthlyaer //layer for eventual bullets
};

//Here we return a speicific ID for a type of component
inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

//We can check the type ID of a generic component here
template<typename T>
inline ComponentID getComponentID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

//The component base class has an owner that refers to an entity
//and some functions to Init, Update and Render the component.
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
	//The entity has a pointer to the scene where is placed.
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
	//This is a list of all the components an entity has
	std::vector<std::unique_ptr<Component>> componentsList;

	ComponentArray componentArray;
	ComponentsSignature componentSignature;
	GroupSignature groupSignature;

public:
	//we can update and render the components by going through the list.
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

	//Check if the entity is alive
	bool isActive() const { return Active; }

	//Group getters and setters
	bool HasGroup(Group group) {
		return groupSignature[group];
	}
	
	void AddGroup(Group group);

	void DelGroup(Group group) {
		groupSignature[group] = false;
	}

	//Kill the entity
	void Kill() { Active = false; }

	//Getters and setters for components
	template<typename T> bool hasComponent() const {
		return componentSignature[getComponentID<T>()];
	}

	//The components arguments are passed here
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) {
		//here we create the component and we set its owner as this entity
		T* cmpnt(new T(std::forward<TArgs>(args)...));
		cmpnt->owner = this;

		//if the Initialization of the component is successful, we proceed
		if (cmpnt->Init()) {
			std::unique_ptr<Component> uPtr{ cmpnt };
			componentsList.emplace_back(std::move(uPtr));

			componentArray[getComponentID<T>()] = cmpnt;
			componentSignature[getComponentID<T>()] = true;
		}
		//otherwise, we delete it
		else {
			delete cmpnt;
		}
		
		return *cmpnt;
	}

	//return a pointer to the component
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class EntityManager {
public:
	//The entity manager has a pointer to the scene where it is placed in, that
	//will later pass in the entity
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

	//Going through the group matrix and updating each entity
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

	//if some requirements are not fullfilled, we will remove the entity from the groups
	void Refresh() {
		//we will start the loop from index 1; we will skip layer zero and one since the tiles wont be deleteted anyway;
		//this will make the game run significantly faster
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
