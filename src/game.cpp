#include "Game.hpp"
bool Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout << "SDL Init failed" << std::endl;
        return false;
    }

    window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        std::cout << "SDL Window failed" << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cout << "SDL Renderer failed" << std::endl;
    }

    if (TTF_Init() != 0) {
        std::cout << "Font failed" << std::endl;
        return false;
    }

    //khoi tao thanh vot
    leftPaddle = new Paddle(0);
    rightPaddle = new Paddle(1);

    //khoi tao bong
    ball = new Ball(this);

    font = TTF_OpenFont("Asset/font.ttf", 32);
    nfont1 = TTF_OpenFont("Asset/menufont.ttf", 120);
    nfont2 = TTF_OpenFont("Asset/menufont.ttf", 48);
    return true;
}

void Game::ShowMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, char* menu, int y){
    MenuSurface = TTF_RenderText_Solid(font, menu, color);
    MenuRect.x = 200;
    MenuRect.y = y;
    MenuRect.w = MenuSurface->w;
    MenuRect.h = MenuSurface->h;
    MenuTexture = SDL_CreateTextureFromSurface(renderer, MenuSurface);
    SDL_RenderCopy(renderer, MenuTexture, NULL, &MenuRect);
}

void Game::ShowCmd(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
    CmdSurface = TTF_RenderText_Solid(font, "PRESS [SPACE] TO CONTINUE", color);
    CmdRect.x = SCREEN_WIDTH / 2 - 250;
    CmdRect.y = 700;
    CmdRect.w = CmdSurface->w;
    CmdRect.h = CmdSurface->h;
    CmdTexture = SDL_CreateTextureFromSurface(renderer, CmdSurface);
    SDL_RenderCopy(renderer, CmdTexture, NULL, &CmdRect);
}
void Game::HandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            GameRunning = false;
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_ESCAPE]) {
        GameRunning = false;
    }

    //trang thai cua game
    if (gamestate == Gamestate::Begin || gamestate == Gamestate::Over){
        if (keystate[SDL_SCANCODE_TAB]){
            gamestate = Gamestate::Help;
            SetGameStateBegin();

        }
    }
    if (gamestate == Gamestate::Help) {
        if (keystate[SDL_SCANCODE_E]) {
            gamestate = Gamestate::Pending;
        }
        return;
    }
    if (gamestate == Gamestate::Pending) {
        if (keystate[SDL_SCANCODE_SPACE]) {
            gamestate = Gamestate::Playing;
        }
        return;
    }

    //dieu khien thanh vot trai
    leftPaddle->SetDirct(0);
    if (keystate[SDL_SCANCODE_W]) {
        leftPaddle->SetDirct(-1);
    }
    if (keystate[SDL_SCANCODE_S]) {
        leftPaddle->SetDirct(1);
    }

    //dieu khien thanh vot phai
    rightPaddle->SetDirct(0);
    if (keystate[SDL_SCANCODE_UP]) {
        rightPaddle->SetDirct(-1);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        rightPaddle->SetDirct(1);
    }

}

void Game::SetGameStatePending() {
    gamestate = Gamestate::Pending;
}
void Game::SetGameStateBegin(){
    leftPaddle->ResetScore(leftPaddle);
    rightPaddle->ResetScore(rightPaddle);
}

void Game::Update() {
    if (gamestate != Gamestate::Playing) {
        return;
    }
    leftPaddle->Update();
    rightPaddle->Update();
    ball->Update(leftPaddle, rightPaddle);
    if (leftPaddle->GetScore() == 5 || rightPaddle->GetScore() == 5){
        gamestate = Gamestate::Over;
    }
}

void Game::Draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
    if (gamestate == Gamestate::Begin){
        ShowMenu(renderer, nfont1, fontColor, "PONG", 100);
        ShowMenu(renderer, nfont2, fontColor, "PRESS [TAB] TO PLAY", 400);
        ShowMenu(renderer, nfont2, fontColor, "PRESS [ESC] TO EXIT", 500);
        SDL_RenderPresent(renderer);
    }

    if (gamestate == Gamestate::Help){
        ShowMenu(renderer, nfont1, fontColor, "PONG", 100);
        ShowMenu(renderer, nfont2, fontColor, "PLAYER 1 CONTROL: [W] AND [S]", 300);
        ShowMenu(renderer, nfont2, fontColor, "PLAYER 2 CONTROL: [ARROW UP] AND [ARROW DOWN]", 400);
        ShowMenu(renderer, nfont2, fontColor, "FIRST TO SCORE 5 POINTS WINS", 500);
        ShowMenu(renderer, nfont2, fontColor, "PRESS [E] TO CONTINUE", 600);
        SDL_RenderPresent(renderer);
    }

    if (gamestate == Gamestate::Playing || gamestate == Gamestate::Pending){

        //ve luoi
        for (int y = 0; y < SCREEN_HEIGHT; y++){
            if (y % 10){
            SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
            }
        }

        //ve thanh vot
        SDL_RenderFillRect(renderer, leftPaddle->GetRect());
        SDL_RenderFillRect(renderer, rightPaddle->GetRect());

        //ve bong
        SDL_RenderFillRect(renderer, ball->GetRect());

        leftPaddle->ShowScore(renderer, font, fontColor, -150, 50);
        rightPaddle->ShowScore(renderer, font, fontColor, 150, 50);

        if (gamestate == Gamestate::Pending) {
            ShowCmd(renderer, font, fontColor);
        }
        SDL_RenderPresent(renderer);
    }
    if (gamestate == Gamestate::Over){
        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
        ShowMenu(renderer, nfont1, fontColor, "GAME OVER", 100);
        if (leftPaddle->GetScore() == 5){
            ShowMenu(renderer, nfont2, fontColor, "PLAYER 1 WINS", 350);
        }
        else {
            ShowMenu(renderer, nfont2, fontColor, "PLAYER 2 WINS", 350);
        }

        ShowMenu(renderer, nfont2, fontColor, "PRESS [TAB] TO PLAY AGAIN", 500);
        SDL_RenderPresent(renderer);
    }
}

void Game::Shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Game::GameLoop() {
    while(GameRunning) {
        HandleEvent();
        Update();
        Draw();
    }
}
