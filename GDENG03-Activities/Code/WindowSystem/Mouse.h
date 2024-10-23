#pragma once
#include <SimpleMath.h>
#include <vector>
#include <unordered_map>

using namespace DirectX::SimpleMath; 

class Mouse
{
#pragma region Mouse-Data-Types
public:
	enum EMouseButtons
	{
		Unknown = 0,
		Left,
		Right,
		Middle
	};

private:
	struct MouseEvents
	{
	public:
		enum class Type
		{
			Unknown = 0,
			LeftPressed,
			LeftReleased,
			RightPressed,
			RightReleased,
			MiddlePressed,
			MiddleReleased,
			WheelUp,
			WheelDown,
			Enter,
			Leave
		};

	public:
		MouseEvents(Vector2 currentPos, Type type) : CurrentPos(currentPos), EventType(type) {}

	public:
		Vector2 CurrentPos;
		Type EventType;
	};
#pragma endregion


public:
	static Mouse* GetInstance();
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	Vector2 GetMousePos();
	bool IsButtonDown(EMouseButtons button);
	bool IsButtonPressed(EMouseButtons button);
	bool IsButtonReleased(EMouseButtons button); 
	bool IsMouseInWindow();
	int GetMouseWheelRotations();
	void FlushEventsBuffer();

private:
	Mouse() {};

	void OnMouseMove(int x, int y);
	void OnMouseChangeFocus(bool isInWindow, int x, int y);
	void OnMousePress(EMouseButtons button, int x, int y);
	void OnMouseRelease(EMouseButtons button, int x, int y);
	void OnMouseWheelRotate(int deltaWheel, int x, int y);

private:
	static Mouse* sharedInstance;

	bool isInWindow = false; 
	Vector2 mousePos = Vector2::Zero;
	int wheelDeltaTotal = 0;
	std::unordered_map<EMouseButtons, bool> buttonStates;
	std::vector<MouseEvents> mouseEventsBuffer;

	friend class Window;
};