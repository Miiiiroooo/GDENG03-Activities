#pragma once
#include <chrono>
#include <ctime>


class GameEngineWindow;

class EngineTime
{
public:
	EngineTime(const EngineTime&) = delete;
	EngineTime& operator=(const EngineTime&) = delete;

	static void Initialize();
	static double GetDeltaTime();
	static void SetTimeScale(float newScale);

private:
	EngineTime() {};
	~EngineTime() {};

	static void LogStartFrame();
	static void LogEndFrame();


private:
	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	double deltaTime;
	double timeSinceStartUp;
	float timeScale;

	friend class GameEngineWindow;
};