#include "Paddle.hpp"

Paddle::Paddle(int i) {
	//tao khung cua thanh vot
	id = i;
	speed = 15.f;

	if (i == 0){
		pos_p.x = 40;
	}
	else if (i == 1) {
		pos_p.x = SCREEN_WIDTH - (width+40);
	}

	pos_p.y = SCREEN_HEIGHT / 2 - height / 2;

	rect.x = (int)pos_p.x;
	rect.y = (int)pos_p.y;
	rect.w = width;
	rect.h = height;
}

int Paddle::GetId() {
	return id;
}

//kiem tra vi tri thanh vot
void Paddle::Update() {
	pos_p.y = pos_p.y + speed*dirct;

	if (pos_p.y < 0) {
		pos_p.y = 0;
	}
	if (pos_p.y + height> SCREEN_HEIGHT) {
		pos_p.y = SCREEN_HEIGHT - height;
	}
	rect.y = pos_p.y;
}
Para Paddle::GetPaddlePos() {
	return pos_p;
}
void Paddle::SetDirct(int d) {
	dirct = d;
}

void Paddle::CountScore() {
	score++;
}

void Paddle::ResetScore(Paddle* paddle){
    paddle->score = 0;
}

void Paddle::ResetPos(Paddle* paddle){
	if (paddle->id == 0){
		pos_p.x = 40;
	}
	else if (paddle->id == 1) {
		pos_p.x = SCREEN_WIDTH - (width+40);
	}

	pos_p.y = SCREEN_HEIGHT / 2 - height / 2;

	rect.x = (int)pos_p.x;
	rect.y = (int)pos_p.y;
}

int Paddle::GetScore(){
    return score;
}

void Paddle::ShowScore(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int x, int y) {
	scoreSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
    scoreRect.x = SCREEN_WIDTH / 2 + x;
	scoreRect.y = y;
	scoreRect.w = scoreSurface->w;
	scoreRect.h = scoreSurface->h;
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}

SDL_Rect* Paddle::GetRect() {
	return &rect;
}
