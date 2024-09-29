#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(Vector2 const& otherVector)
{
	return Vector2(x + otherVector.x, y + otherVector.y);
}

Vector2& Vector2::operator+=(Vector2 const& otherVector)
{
	x += otherVector.x;
	y += otherVector.y;

	return *this;
}

Vector2 Vector2::operator-(Vector2 const& otherVector)
{
	return Vector2(x - otherVector.x, y - otherVector.y);
}

Vector2 Vector2::operator*(float otherFloat)
{
	return Vector2(x * otherFloat, y * otherFloat);
}
