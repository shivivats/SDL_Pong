#include "Pong.h"
#include <SDL.h>
#include <iostream>
#include "Vector2.h"
#include "Ball.h"
#include "Paddle.h"
#include <SDL_ttf.h>
#include "PlayerScore.h"
#include <chrono>

int Pong::game()
{

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Renderer* renderer = NULL;

	TTF_Font* scoreFont = NULL;

	// Initialise SDL and SDL_TTF
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{

		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);

			// Initialise the font
			scoreFont = TTF_OpenFont("Fonts\\RobotoMono-VariableFont_wght.ttf", 40);

			// Render one score at 1/4th of the width and the other at 3/4ths of the width of window
			PlayerScore playerOneScoreText(Vector2(WINDOW_WIDTH / 4, 20), renderer, scoreFont, scoreColor);
			PlayerScore playerTwoScoreText(Vector2(3 * WINDOW_WIDTH / 4, 20), renderer, scoreFont, scoreColor);

			// Create ball
			Ball ball(
				Vector2((WINDOW_WIDTH / 2.0f) - (Ball::BALL_WIDTH / 2.0f),
					(WINDOW_HEIGHT / 2.0f) - (Ball::BALL_WIDTH / 2.0f)),
				Vector2(Ball::BALL_SPEED, 0.0f));

			// Create both paddles
			Paddle paddleOne(
				Vector2(50.f, (WINDOW_HEIGHT / 2.0f) - (Paddle::PADDLE_HEIGHT / 2.0f)),
				Vector2(0.0f, 0.0f));

			Paddle paddleTwo(
				Vector2(WINDOW_WIDTH - 50.f, (WINDOW_HEIGHT / 2.0f) - (Paddle::PADDLE_HEIGHT / 2.0f)),
				Vector2(0.0f, 0.0f));

			// Game Logic
			{
				int playerOneScore = 0;
				int playerTwoScore = 0;
				
				bool running = true;

				bool buttons[4] = {};


				float deltaTime = 0.0f;

				while (running)
				{
					auto startTime = std::chrono::high_resolution_clock::now();

					SDL_Event event;
					while (SDL_PollEvent(&event))
					{
						if (event.type == SDL_QUIT)
						{
							running = false;
						}
						else if (event.type == SDL_KEYDOWN)
						{
							if (event.key.keysym.sym == SDLK_ESCAPE)
							{
								running = false;
							}
							else if (event.key.keysym.sym == SDLK_w)
							{
								buttons[Buttons::PaddleOneUp] = true;
							}
							else if (event.key.keysym.sym == SDLK_s)
							{
								buttons[Buttons::PaddleOneDown] = true;
							}
							else if (event.key.keysym.sym == SDLK_UP)
							{
								buttons[Buttons::PaddleTwoUp] = true;
							}
							else if (event.key.keysym.sym == SDLK_DOWN)
							{
								buttons[Buttons::PaddleTwoDown] = true;
							}
						}
						else if (event.type == SDL_KEYUP)
						{
							if (event.key.keysym.sym == SDLK_w)
							{
								buttons[Buttons::PaddleOneUp] = false;
							}
							else if (event.key.keysym.sym == SDLK_s)
							{
								buttons[Buttons::PaddleOneDown] = false;
							}
							else if (event.key.keysym.sym == SDLK_UP)
							{
								buttons[Buttons::PaddleTwoUp] = false;
							}
							else if (event.key.keysym.sym == SDLK_DOWN)
							{
								buttons[Buttons::PaddleTwoDown] = false;
							}
						}
					}

					// Set paddle velocities according to keypresses
					if (buttons[Buttons::PaddleOneUp])
					{
						paddleOne.velocity.y = -Paddle::PADDLE_SPEED;
					}
					else if (buttons[Buttons::PaddleOneDown])
					{
						paddleOne.velocity.y = Paddle::PADDLE_SPEED;
					}
					else
					{
						paddleOne.velocity.y = 0.0f;
					}

					if (buttons[Buttons::PaddleTwoUp])
					{
						paddleTwo.velocity.y = -Paddle::PADDLE_SPEED;
					}
					else if (buttons[Buttons::PaddleTwoDown])
					{
						paddleTwo.velocity.y = Paddle::PADDLE_SPEED;
					}
					else
					{
						paddleTwo.velocity.y = 0.0f;
					}

					// Update the paddle positions
					paddleOne.Update(deltaTime);
					paddleTwo.Update(deltaTime);

					// Update the ball position
					ball.Update(deltaTime);

					// Check for collisions between paddles and ball
					Contact contact = CheckPaddleCollision(ball, paddleOne);

					if (contact.type != CollisionType::None)
					{
						ball.CollideWithPaddle(contact);
					}

					contact = CheckPaddleCollision(ball, paddleTwo);
					if (contact.type != CollisionType::None)
					{
						ball.CollideWithPaddle(contact);
					}

					// Check for collisions between ball and walls
					contact = CheckWallCollision(ball);
					if (contact.type != CollisionType::None)
					{
						ball.CollideWithWall(contact);

						if (contact.type == CollisionType::WallLeft)
						{
							playerTwoScore++;
							playerTwoScoreText.SetScore(playerTwoScore, scoreColor);
						}
						else if (contact.type == CollisionType::WallRight)
						{
							playerOneScore++;
							playerOneScoreText.SetScore(playerOneScore, scoreColor);
						}
					}

					// Clear the window to black
					SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
					SDL_RenderClear(renderer);

					// 
					// Rendering will happen here
					//

					// Set the draw color to be white
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					// Draw the net
					for (int y = 0; y < WINDOW_HEIGHT; ++y)
					{
						if (y % 5)
						{
							SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
						}
					}

					// Draw the ball
					ball.Draw(renderer);

					// Draw both paddles
					paddleOne.Draw(renderer);
					paddleTwo.Draw(renderer);

					// Display the scores
					playerOneScoreText.Draw();
					playerTwoScoreText.Draw();

					// Render anything that happened since the last rendering call
					SDL_RenderPresent(renderer);

					// Calculate frame time
					auto stopTime = std::chrono::high_resolution_clock::now();
					deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
				}
			}
		}
	}



	// Cleanup
	SDL_DestroyRenderer(renderer); // Destroy Renderer
	SDL_DestroyWindow(window); //Destroy window
	TTF_CloseFont(scoreFont); // Close the font
	TTF_Quit(); // Quit SDL_TTF
	SDL_Quit(); //Quit SDL subsystems

	return 0;
}



/*
* Check for collision between paddle and ball by projecting both on to x and y axes
*/
Contact Pong::CheckPaddleCollision(Ball const& ball, Paddle const& paddle)
{
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + Ball::BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + Ball::BALL_HEIGHT;

	float paddleLeft = paddle.position.x;
	float paddleRight = paddle.position.x + Paddle::PADDLE_WIDTH;
	float paddleTop = paddle.position.y;
	float paddleBottom = paddle.position.y + Paddle::PADDLE_HEIGHT;

	Contact contact{};

	// if the ball is completely outside of the paddle, then we are not colliding
	if (ballLeft >= paddleRight
		|| ballRight <= paddleLeft
		|| ballTop >= paddleBottom
		|| ballBottom <= paddleTop)
	{
		return contact;
	}

	float paddleRangeUpper = paddleBottom - (2.0f * Paddle::PADDLE_HEIGHT / 3.0f);
	float paddleRangeMiddle = paddleBottom - (Paddle::PADDLE_HEIGHT / 3.0f);

	if (ball.velocity.x < 0)
	{
		// Left paddle contact
		contact.penetration = paddleRight - ballLeft;
	}
	else if (ball.velocity.x > 0)
	{
		// Right paddle contact
		contact.penetration = paddleLeft - ballRight;
	}

	if ((ballBottom > paddleTop)
		&& (ballBottom < paddleRangeUpper))
	{
		contact.type = CollisionType::PaddleTop;
	}
	else if ((ballBottom > paddleRangeUpper)
		&& (ballBottom < paddleRangeMiddle))
	{
		contact.type = CollisionType::PaddleMiddle;
	}
	else
	{
		contact.type = CollisionType::PaddleBottom;
	}

	return contact;
}

Contact Pong::CheckWallCollision(Ball const& ball)
{
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + Ball::BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + Ball::BALL_HEIGHT;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::WallLeft;
	}
	else if (ballRight > WINDOW_WIDTH)
	{
		contact.type = CollisionType::WallRight;
	}
	else if (ballTop < 0.0f)
	{
		contact.type = CollisionType::WallTop;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > WINDOW_HEIGHT)
	{
		contact.type = CollisionType::WallBottom;
		contact.penetration = WINDOW_HEIGHT - ballBottom;
	}

	return contact;
}