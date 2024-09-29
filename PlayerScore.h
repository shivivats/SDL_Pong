#pragma once
#include "Vector2.h"
#include <SDL_ttf.h>
#include <SDL.h>

class PlayerScore
{

public:
	PlayerScore(Vector2 position, SDL_Renderer* renderer, TTF_Font* font, SDL_Color scoreColor);

	~PlayerScore();

	void Draw();

	void SetScore(int score, SDL_Color scoreColor);

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface{};
	SDL_Texture* texture{};
	SDL_Rect rect{};
};

