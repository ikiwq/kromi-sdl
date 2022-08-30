#include "Timer.h"
#include <iostream>

Timer* Timer::Instance = NULL;

Timer* Timer::GetInstance() {
	if (Instance == NULL) {
		Instance = new Timer();
	}
	return Instance;
}

Timer::Timer() {
	Reset();
	ScaleTime = 1.0f;
}

Timer::~Timer() {
	delete Instance;
	Instance = nullptr;
}

void Timer::Clear() {
	delete Instance;
	Instance = nullptr;
}


void Timer::Reset() {
	StartTicks = SDL_GetTicks();
	ElapsedTicks = 0;
	dT = 0;
}

void Timer::Update() {
	ElapsedTicks = SDL_GetTicks() - StartTicks;
	dT = ElapsedTicks * 0.001f;
}

float Timer::GetDt() {
	return dT * ScaleTime;
}

void Timer::ResetPhysics() {
	PhysicsStartTicks = SDL_GetTicks();
	PhysicsElapsedTicks = 0;
	PhysicsdT = 0;
}

void Timer::UpdatePhysics() {
	PhysicsElapsedTicks = SDL_GetTicks() - PhysicsStartTicks;
	PhysicsdT = PhysicsElapsedTicks * 0.001f;
}

float Timer::GetPhysicsDt() {
	return PhysicsdT >= 0.5 ? 0.5 : PhysicsdT * ScaleTime;
}