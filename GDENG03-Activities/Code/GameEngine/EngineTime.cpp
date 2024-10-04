#include "EngineTime.h"


EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::Initialize()
{
	sharedInstance = new EngineTime();
	sharedInstance->deltaTime = 0;
	sharedInstance->timeSinceStartUp = 0;
}

double EngineTime::GetDeltaTime()
{
	return sharedInstance->deltaTime;
}

void EngineTime::SetTimeScale(float newScale)
{
	if (newScale < 0) return;
	sharedInstance->timeScale = newScale;
}

void EngineTime::LogStartFrame()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogEndFrame()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedInSeconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsedInSeconds.count() / (double)sharedInstance->timeScale;
	sharedInstance->timeSinceStartUp += elapsedInSeconds.count();
}