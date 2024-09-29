#pragma once
#include "Vector2.h"
#include <SDL.h>

class Paddle
{
public:

	Paddle(Vector2 position, Vector2 velocity);

	void Draw(SDL_Renderer* renderer);

	void Update(float deltaTime);

	Vector2 position;
	Vector2 velocity;
	SDL_Rect rect{};

	static const int PADDLE_WIDTH = 10;
	static const int PADDLE_HEIGHT = 100;
	static const int PADDLE_SPEED = 1.0f;
};

