#pragma once
#include <windows.h>
#include <iostream>

enum class VerticalDirectionType
{
	Up = -1,
	None = 0,
	Down = 1,
};

enum class HorizontalDirectionType
{
	Left = -1,
	None = 0,
	Right = 1,
};

struct MoveDirection {
	HorizontalDirectionType HorizontalDirection = HorizontalDirectionType::None;
	VerticalDirectionType VerticalDirection = VerticalDirectionType::None;
};

class MoveableRectangle
{
	public:

		MoveableRectangle(LONG leftPos = 0, LONG topPos = 0, LONG rightPos = 100, LONG bottomPos = 100);

		RECT RectObject;
		MoveDirection Direction;

		void ChangeSpeed(char offset);

		char GetSpeed() { return _rectSpeed; }

		char GetXVectorSpeed() { return _rectSpeed * static_cast<char>(Direction.HorizontalDirection); }
		char GetYVectorSpeed() { return _rectSpeed * static_cast<char>(Direction.VerticalDirection); }

		const char MAX_SPEED = 100;
		const char MIN_SPEED = 0;

	private:
		char GetNewSpeed(char oldSpeed, char speedChangeValue);
		char _rectSpeed = 0;

};
