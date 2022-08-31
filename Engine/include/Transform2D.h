#pragma once

#include "ECS.h"
#include "Maths.h"
#include "Timer.h"

//The transform component contains an "absolute" position(that is NOT the rendering position on the screen)
//It also contains Vectors with various infos

class Transform2D : public Component {
public:
	Vector2 Position;
	Vector2 Velocity;
	Vector2 Acceleration;
	Vector2 Scale;
	float rotation;
private:
	Timer* timer;
	float dt;
public:
	Transform2D(float x, float y) :
		rotation(0), dt(0) {
		Position.x = x;
		Position.y = y;
		timer = Timer::GetInstance();
	}
	~Transform2D() = default;

	//Setters and Getters

	//Position
	void SetPosition(Vector2 Pos) {
		Position.x = Pos.x;
		Position.y = Pos.y;
	}

	void SetPosition(float x, float y) {
		Position.x = x;
		Position.y = y;
	}

	Vector2 GetPosition() {
		return Position;
	}

	void SetVelocity(Vector2 vec) {
		Velocity.x = vec.x;
		Velocity.y = vec.y;
	}

	void SetVelocity(float vecx, float vecy) {
		Velocity.x = vecx;
		Velocity.y = vecy;
	}

	Vector2 GetVelocity() {
		return Velocity;
	}

	//Acceleration
	void SetAcceleration(Vector2 acc) {
		Acceleration.x = acc.x;
		Acceleration.y = acc.y;
	}

	void SetAcceleration(float accx, float accy) {
		Acceleration.x = accx;
		Acceleration.y = accy;
	}

	Vector2 GetAcceleration() {
		return Acceleration;
	}

	//Scale
	void SetScale(Vector2 scale) {
		Scale.x = scale.x;
		Scale.y = scale.y;
	}
	void SetScale(float scalex, float scaley) {
		Scale.x = scalex;
		Scale.y = scaley;
	}

	Vector2 GetScale() {
		return Scale;
	}

	//Rotation
	void SetRotation(float rot) {
		rotation = rot;
	}

	float GetRotation() {
		return rotation;
	}

	//Default functions
	bool Init() override final {
		//Dependencies
		if (owner->hasComponent<Transform2D>()) {
			std::cout << "Entity has already got Transform Component!" << std::endl;
			return false;
		}

		Velocity.x = 0;
		Velocity.y = 0;
		Acceleration.x = 0;
		Acceleration.y = 0;
		rotation = 0;
		Scale.x = 1;
		Scale.y = 1;

		return true;
	}

	void Update() override final {
		//Gets the delta time for calculations
		dt = timer->GetPhysicsDt();

		//The scale is calculated by dividing the Window size by the Camera size
		Scale.x = owner->EntityScene->graphics->VideoX / owner->EntityScene->Camera.w;
		Scale.y = owner->EntityScene->graphics->VideoY / owner->EntityScene->Camera.h;

		//Calculations for Position
		Velocity.x += Acceleration.x * dt;
		Velocity.y += Acceleration.y * dt;

		Position.x += Velocity.x * dt;
		Position.y += Velocity.y * dt;
	}
};