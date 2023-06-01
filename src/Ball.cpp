#include "Ball.hpp"

Ball::Ball(Game* g) {
	game = g;
	speed = InitSpeed;

	pos.x = SCREEN_WIDTH / 2 - b_width / 2;
	pos.y = SCREEN_HEIGHT / 2 - b_height / 2;

	vel.x = 1;
	vel.y = 1;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = b_width;
	rect.h = b_height;
}

//kiem tra tuong tac giua bong va thanh vot
bool Ball::BotCollCheck(Paddle* paddle) {
	bool Passedboundry = false;
	bool Collide = false;
	if (paddle->GetId() == 0) {
		Passedboundry = pos.x < b_width;
	}
	if (paddle->GetId() == 1) {
		Passedboundry = pos.x > SCREEN_WIDTH - b_width;
	}
	if (Passedboundry
		&& pos.y <= paddle->GetRect()->y + paddle->GetRect()->h
		&& pos.y + b_height <= paddle->GetRect()->y + paddle->GetRect()->h
		&& vel.y < 0)
	{
		pos.y = paddle->GetRect()->y + paddle->GetRect()->h+1;
		vel.y *= -1;
		rect.y = pos.y;
		Collide = true;
	}
	return Collide;
}
bool Ball::TopCollCheck(Paddle* paddle) {
	bool Passedboundry = false;
	bool Collide = false;
	if (paddle->GetId() == 0) {
		Passedboundry = pos.x < b_width;
	}
	if (paddle->GetId() == 1) {
		Passedboundry = pos.x > SCREEN_WIDTH - b_width;
	}
	if (Passedboundry
		&& pos.y + b_height >= paddle->GetRect()->y
		&& pos.y < paddle->GetRect()->y
		&& vel.y < 0)
	{
		pos.y = paddle->GetRect()->y - b_height - 1;
		vel.y *= -1;
		rect.y = pos.y;
		Collide = true;
	}
	return Collide;
}

void Ball::CollCheck(Paddle* paddle) {
	if (BotCollCheck(paddle) || TopCollCheck(paddle)){
		return;
	}
	if (pos.x + b_width >= paddle->GetPaddlePos().x
		&& pos.x <= paddle->GetRect()->w + paddle->GetPaddlePos().x
		&& pos.y + b_height >= paddle->GetPaddlePos().y
		&& pos.y <= paddle->GetPaddlePos().y + paddle->GetRect()->h)
	{
		vel.x *= -1;
		int MidPadColl = paddle->GetPaddlePos().y + paddle->GetRect()->h;
		int MidBallColl = pos.y + b_height / 2;
		int offsetY = MidPadColl - MidBallColl;
		vel.y -= offsetY * 1.5 / 120.f;
		if (paddle->GetId() == 0) {
			pos.x = paddle->GetPaddlePos().x + paddle->GetRect()->w;
		}
		if (paddle->GetId() == 1) {
			pos.x = paddle->GetPaddlePos().x - b_width;
		}

		if (speed < MaxSpeed) {
			speed++;
		}
	}
}

SDL_Rect* Ball::GetRect(){
	return &rect;
}

void Ball::Update(Paddle* lpaddle, Paddle* rpaddle){
	//xac dinh huong di cua bong
	pos.x = pos.x + vel.x * speed;
	pos.y = pos.y + vel.y * speed;

	if (pos.x < 0) {
		rpaddle->CountScore();
		Reset(lpaddle,rpaddle);
	}
	if (pos.x>SCREEN_WIDTH - b_width) {
		lpaddle->CountScore();
		Reset(lpaddle, rpaddle);
	}
	CollCheck(lpaddle);
	CollCheck(rpaddle);

	//xac dinh bien cua bong
	if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1;
	}
	if (pos.y + b_height > SCREEN_HEIGHT) {
		pos.y = SCREEN_HEIGHT - b_height;
		vel.y *= -1;
	}
	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
}

void Ball::Reset(Paddle* lpaddle, Paddle* rpaddle) {
	speed = InitSpeed;

	pos.x = SCREEN_WIDTH / 2 - b_width / 2;
	pos.y = SCREEN_HEIGHT / 2 - b_height / 2;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	lpaddle->ResetPos(lpaddle);
	rpaddle->ResetPos(rpaddle);
	game->SetGameStatePending();
}
