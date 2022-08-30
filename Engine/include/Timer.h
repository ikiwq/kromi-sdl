#pragma once

#include "SDL.h"

class Timer {
public:
	const int FPS = 144;
	const int PhysicsCallPerSeconds = 300;
private:
	static Timer* Instance;

	unsigned int StartTicks;
	unsigned int ElapsedTicks;
	float dT;

	unsigned int PhysicsStartTicks;
	unsigned int PhysicsElapsedTicks;
	float PhysicsdT;

	float ScaleTime;

public:
	static Timer* GetInstance();
	static void Clear();

	void Reset();
	float GetDt();
	void Update();

	void ResetPhysics();
	float GetPhysicsDt();
	void UpdatePhysics();

private:
	Timer();
	~Timer();
};
