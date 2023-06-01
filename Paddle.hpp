#pragma once
#include "Utils.hpp"

class Paddle
{
public:
	Paddle(int i);
	void Update();
	void SetDirct(int d);
	void ResetPos(Paddle* paddle);
	int GetId();
	int GetScore();
	void ResetScore(Paddle* paddle);
	void CountScore();
	void ShowScore(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int x, int y);
	Para GetPaddlePos();
	SDL_Rect *GetRect();

private:
	int id;
	int dirct = 0;
	int width = 20;
	int height = 140;
	float speed;
	int score = 0;

	Para pos_p;
	SDL_Rect rect;
	SDL_Rect scoreRect;
	SDL_Surface* scoreSurface = nullptr;
	SDL_Texture* scoreTexture = nullptr;
};

