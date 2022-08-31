#include "Timer.h"
#include <iostream>

//The timer calculates the delta time. There are 2 delta times: one between each render(dT) and one between
//each update(PhysicsdT). This allows for two separatd loops, one for updating and one for rendering.

Timer* Timer::Instance = nullptr;

Timer* Timer::GetInstance() {
	//This class is a singleton
	if (Instance == nullptr) {
		Instance = new Timer();
	}
	return Instance;
}

Timer::Timer() {
	//In the constructor, the timer is reset and the time scale is set to 1
	Reset();
	TimeScale = 1.0f;
}

Timer::~Timer() {
}

void Timer::Clear() {
	delete Instance;
	Instance = nullptr;
}

//Resets the dT between frames
void Timer::Reset() {
	StartTicks = SDL_GetTicks();
	ElapsedTicks = 0;
	dT = 0;
}

//Updates the dT between frames
void Timer::Update() {
	ElapsedTicks = SDL_GetTicks() - StartTicks;
	dT = ElapsedTicks * 0.001f * TimeScale;
}

//Returns the dT between frames
float Timer::GetDt() {
	return dT * TimeScale;
}

//Resets the dT between updates
void Timer::ResetPhysics() {
	PhysicsStartTicks = SDL_GetTicks();
	PhysicsElapsedTicks = 0;
	PhysicsdT = 0;
}

//Updates the dT between updates
void Timer::UpdatePhysics() {
	PhysicsElapsedTicks = SDL_GetTicks() - PhysicsStartTicks;
	PhysicsdT = PhysicsElapsedTicks * 0.001f;
}

//Returns the dT between updates
float Timer::GetPhysicsDt() {
	return PhysicsdT >= 0.5 ? 0.5 : PhysicsdT * TimeScale;
}