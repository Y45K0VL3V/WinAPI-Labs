#include "MoveableRectangle.h"

MoveableRectangle::MoveableRectangle(LONG leftPos, LONG topPos, LONG rightPos, LONG bottomPos)
{
	RectObject.left = leftPos;
	RectObject.top = topPos;
	RectObject.right = rightPos;
	RectObject.bottom = bottomPos;
}

BOOL IsNewSpeedValid(char oldSpeed, char speedChangeValue)
{
	short newSpeed = oldSpeed + speedChangeValue;
	return (newSpeed <= 100 && newSpeed >= 0);
}

char MoveableRectangle::ChangeXSpeed(char dx)
{
	if (IsNewSpeedValid(_rectYSpeed, dx))
		_rectYSpeed += dx;

	return _rectYSpeed;
}

char MoveableRectangle::ChangeYSpeed(char dy)
{
	if (IsNewSpeedValid(_rectYSpeed, dy))
		_rectYSpeed += dy;

	return _rectYSpeed;
}