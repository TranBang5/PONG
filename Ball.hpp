#pragma once
#include "Paddle.hpp"
#include "Game.hpp"

class Ball
{
public:
	Ball(class Game* g);
	void Update(Paddle* lpaddle, Paddle* rpaddle);
	void CollCheck(Paddle* paddle);
	bool BotCollCheck(Paddle* paddle);
	bool TopCollCheck(Paddle* paddle);
	void Reset(Paddle* lpaddle, Paddle* rpaddle);

	SDL_Rect* GetRect();

private:
	int dirct = 0;
	int b_height = 20;
	int b_width = 20;
	float speed;
	const int InitSpeed = 4.f;
	const int MaxSpeed = 6.f;
	Para pos;
	Para vel;
	SDL_Rect rect;
	Game* game;
};

