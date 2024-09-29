#include "PlayerScore.h"
#include <string>

PlayerScore::PlayerScore(Vector2 position, SDL_Renderer* renderer, TTF_Font* font, SDL_Color scoreColor)
{
	this->renderer = renderer;
	this->font = font;

	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	SetScore(0, scoreColor);
}

PlayerScore::~PlayerScore()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void PlayerScore::Draw()
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void PlayerScore::SetScore(int score, SDL_Color scoreColor)
{
	// free old surface and texture
	if (surface != nullptr)
		SDL_FreeSurface(surface);
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	// make new surface and texture
	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), scoreColor); // Set surface to the font surface, with score text and colour
	texture = SDL_CreateTextureFromSurface(renderer, surface); // create a texture to be drawn on the screen
	
	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}
