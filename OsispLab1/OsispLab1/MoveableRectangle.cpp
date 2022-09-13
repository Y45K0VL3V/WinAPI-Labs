#include "MoveableRectangle.h"

MoveableRectangle::MoveableRectangle(LONG leftPos, LONG topPos, LONG rightPos, LONG bottomPos)
{
	RectObject.left = leftPos;
	RectObject.top = topPos;
	RectObject.right = rightPos;
	RectObject.bottom = bottomPos;
}

char MoveableRectangle::GetNewSpeed(char oldSpeed, char speedChangeValue)
{
	short newSpeed = oldSpeed + speedChangeValue;
	
	if (newSpeed > MAX_SPEED) return MAX_SPEED;
	if (newSpeed < MIN_SPEED) return MIN_SPEED;
	
	return newSpeed;
}

void MoveableRectangle::ChangeSpeed(char offset)
{
	_rectSpeed = GetNewSpeed(_rectSpeed, offset);
}