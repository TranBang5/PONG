#pragma once
#include "Ball.hpp"

enum Gamestate {
    Begin,
    Help,
    Pending,
    Playing,
    Over
};

class Game
{
public:
    bool Init();
    void GameLoop();
    void Shutdown();
    void SetGameStatePending();
    void SetGameStateBegin();
    void ShowCmd(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
    void ShowMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, char* menu, int y);
    bool GameOver(Paddle* lpaddle, Paddle* rpaddle);
private:
    void HandleEvent();
    void Update();
    void Draw();

    int gamestate = Gamestate::Begin;
    bool GameRunning = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    class Paddle *leftPaddle, * rightPaddle;
    class Ball *ball;

    TTF_Font* font = nullptr;
    TTF_Font* nfont1 = nullptr;
    TTF_Font* nfont2 = nullptr;
    SDL_Color fontColor = { 225, 225, 225 };

    SDL_Rect CmdRect;
    SDL_Surface* CmdSurface = nullptr;
    SDL_Texture* CmdTexture = nullptr;

    SDL_Rect MenuRect;
    SDL_Surface* MenuSurface = nullptr;
    SDL_Texture* MenuTexture = nullptr;
};

