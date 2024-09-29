#include "Ball.h"
#include "Pong.h"

Ball::Ball(Vector2 position, Vector2 velocity)
{
	this->position = position;
	this->velocity = velocity;
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = BALL_WIDTH;
	rect.h = BALL_HEIGHT;
}

void Ball::Draw(SDL_Renderer* renderer)
{
	// update the ball's position
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	// render the ball as a rect
	SDL_RenderFillRect(renderer, &rect);
}

void Ball::Update(float deltaTime)
{
	position += velocity * deltaTime;
}

void Ball::CollideWithPaddle(Contact const& contact)
{
	position.x += contact.penetration;
	velocity.x = -velocity.x;

	if (contact.type == CollisionType::PaddleTop)
	{
		velocity.y = -0.75f * BALL_SPEED;
	}
	else if (contact.type == CollisionType::PaddleBottom)
	{
		velocity.y = 0.75f * BALL_SPEED;
	}

}

void Ball::CollideWithWall(Contact const& contact)
{
	if ((contact.type == CollisionType::WallTop)
		|| (contact.type == CollisionType::WallBottom))
	{
		position.y += contact.penetration;
		velocity.y = -velocity.y;
	}
	else if (contact.type == CollisionType::WallLeft)
	{
		position.x = Pong::WINDOW_WIDTH / 2.0f;
		position.y = Pong::WINDOW_HEIGHT / 2.0f;
		velocity.x = BALL_SPEED;
		//velocity.y = 0.75f * BALL_SPEED;
		velocity.y = 0.0f; // Custom change: make the ball go straight instead of at an angle upon going out of bounds
	}
	else if (contact.type == CollisionType::WallRight)
	{
		position.x = Pong::WINDOW_WIDTH / 2.0f;
		position.y = Pong::WINDOW_HEIGHT / 2.0f;
		velocity.x = -BALL_SPEED;
		//velocity.y = 0.75f * BALL_SPEED;
		velocity.y = 0.0f; // Custom change: make the ball go straight instead of at an angle upon going out of bounds
	}
}
