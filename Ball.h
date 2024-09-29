#pragma once
#include "Vector2.h"
#include <SDL.h>

enum class CollisionType
{
	None,
	PaddleTop,
	PaddleMiddle,
	PaddleBottom,
	WallTop,
	WallBottom,
	WallLeft,
	WallRight
};

struct Contact
{
	CollisionType type;
	float penetration;
	// the penetration is needed to move the ball outside of the paddle/wall edge to avoid any weird getting stuck scenarios with collision
};

class Ball
{
public:
	Ball(Vector2 position, Vector2 velocity);

	void Draw(SDL_Renderer* renderer);

	void Update(float deltaTime);

	void CollideWithPaddle(Contact const& contact);

	void CollideWithWall(Contact const& contact);

	Vector2 position;
	Vector2 velocity;

	SDL_Rect rect{};

	static const int BALL_WIDTH = 15;
	static const int BALL_HEIGHT = 15;
	static const int BALL_SPEED = 1.0f;
};

