#pragma once

#include <SDL.h>
#include "Ball.h"
#include "Paddle.h"

/*
* REMEMBER THAT SDL SETS THE ORIIGN AT TOP LEFT!
*/

const SDL_Color scoreColor = { 0xFF, 0xFF, 0xFF, 0xFF };

enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown
};

class Pong
{

public:
	int game();

	Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle);
	Contact CheckWallCollision(Ball const& ball);

	static const int WINDOW_HEIGHT = 720;
	static const int WINDOW_WIDTH = 1280;
};

