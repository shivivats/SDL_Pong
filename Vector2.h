#pragma once
class Vector2
{
public:
	Vector2();

	Vector2(float x, float y);

	// Overloaded operations
	Vector2 operator+(Vector2 const& otherVector);

	Vector2& operator+=(Vector2 const& otherVector);

	Vector2 operator-(Vector2 const& otherVector);

	Vector2 operator*(float otherFloat);

	// Components of the 2D vector
	float x;

	float y;
};

