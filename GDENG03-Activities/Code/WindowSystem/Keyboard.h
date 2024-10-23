#pragma once
#include <unordered_map>
#include <vector>

class Keyboard
{
#pragma region Keyboard-Data-Types
private:
	struct KeyboardEvents
	{
	public:
		enum class Type
		{
			Unknown,
			Pressed,
			Released
		};

	public:
		KeyboardEvents(unsigned char key, Type type) : Key(key), EventType(type) {}

	public:
		unsigned char Key;
		Type EventType;
	};
#pragma endregion


public:
	static Keyboard* GetInstance();
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	bool IsKeyDown(unsigned char key);
	bool IsKeyPressed(unsigned char key);
	bool IsKeyReleased(unsigned char key);
	std::vector<char>& GetCharBuffer();

	void FlushEventsBuffer();
	void FlushCharBuffer();

private:
	Keyboard() {};

	void OnKeyPressed(unsigned char key);
	void OnKeyReleased(unsigned char key);
	void OnChar(char character);


private:
	static Keyboard* sharedInstance; 

	std::unordered_map<unsigned char, bool> keyStates;
	std::vector<KeyboardEvents> keyEventsBuffer;
	std::vector<char> charBuffer;

	friend class Window;
};