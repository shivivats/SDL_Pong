#include "Paddle.h"
#include "Pong.h"

Paddle::Paddle(Vector2 position, Vector2 velocity)
{
	this->position = position;
	this->velocity = velocity;
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = PADDLE_WIDTH;
	rect.h = PADDLE_HEIGHT;
}

void Paddle::Draw(SDL_Renderer* renderer)
{
	// update the y pos because the paddle wont move in x
	rect.y = static_cast<int>(position.y);
	
	// render the paddle as a rect
	SDL_RenderFillRect(renderer, &rect);
}

void Paddle::Update(float deltaTime)
{
	position += velocity * deltaTime;

	if (position.y < 0)
	{
		// restrict to the top of the screen
		position.y = 0;
	}
	else if (position.y > (Pong::WINDOW_HEIGHT - PADDLE_HEIGHT))
	{
		// restrict to the bottom of the screen
		position.y = Pong::WINDOW_HEIGHT - PADDLE_HEIGHT;
	}
}
