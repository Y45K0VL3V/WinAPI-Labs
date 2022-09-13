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

		char ChangeXSpeed(char dx);
		char ChangeYSpeed(char dy);

	private:
		char _rectXSpeed = 0;
		char _rectYSpeed = 0;

};
