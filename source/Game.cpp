

#include "Game.h"
#include "Exceptions/SDL_Exception.h"
#include "Engine/Graphics/Texture.h"
#include "Hero.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Input/Keyboard.h"
#include "Brick.h"






const int UP = 1;
const int DOWN = 2;
//const int RIGHT = 2;
Keyboard* keyboard;
Keyboard* keyboard2;

void Game::Init() {
    InitSDL();
    CreateWindowAndRender();
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  
    _logoTexture = new Texture("resources/Backgroung.jpg", _renderer,0);
    _logoTexture->Init();
    _destLogoRect.x = 0;
    _destLogoRect.y = 0;
    _destLogoRect.w = 800; 
    _destLogoRect.h = 600;

    _destPP1Rect.x = 75;
    _destPP1Rect.y = 495;
    

    _destPP2Rect.x = 460;
    _destPP2Rect.y = 495;
    

    livesP1.resize(3);
    livesP2.resize(3);

    for (int i = 0; i < livesP1.size(); i++) {
        livesP1.at(i) = new Texture("resources/platform.png", _renderer, 0);
        livesP1.at(i)->Init();
    }
    for (int i = 0; i < livesP2.size(); i++) {
        livesP2.at(i) = new Texture("resources/platform.png", _renderer, 0);
        livesP2.at(i)->Init();
    }
    

    _inputHandler = new InputHandler();
    keyboard = new Keyboard();
    keyboard2 = new Keyboard();
    //auto button1 = InputButton{JUMP, SDLK_d};
    auto button1 = InputButton{ UP, SDLK_w };
    auto button2 = InputButton{ DOWN, SDLK_s };
    auto button3 = InputButton{ UP, SDLK_UP };
    auto button4 = InputButton{ DOWN, SDLK_DOWN };
    keyboard->AddButtonMap(button1);
    keyboard->AddButtonMap(button2);
    keyboard2->AddButtonMap(button3);
    keyboard2->AddButtonMap(button4);
    _inputHandler->AddController(keyboard);
    _inputHandler->AddController(keyboard2);

    _hero = new Hero(_renderer, keyboard,90,10,300,80,20,0);
    _hero->Init();

    _hero2 = new Hero(_renderer, keyboard2, -90, 710, 300, 80, 20, 0);
    _hero2->Init();

    
    
    _map = new Map(_renderer);
    _map->Init();

    _isRunning = true;
}

void Game::InitSDL() {
    auto isInitialized = SDL_Init(SDL_INIT_VIDEO) >= 0;

    if (!isInitialized) {
        throw SDL_Exception(SDL_GetError());
    }
}

void Game::CreateWindowAndRender() {
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &_window, &_renderer);

    if (_window == nullptr || _renderer == nullptr) {
        throw SDL_Exception(SDL_GetError());
    }
}


void Game::HandleEvents() {
    _inputHandler->PreHandleEvent();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _isRunning = false;
        }
        else {
            _inputHandler->HandleEvent(&event);
        }
    }
}

void Game::Update(double elapsedSeconds) {
    if (keyboard->GetButtonDown(UP) || keyboard2->GetButtonDown(UP)) {
        printf("UP ");
    }

    else if (keyboard->GetButtonUp(DOWN) || keyboard2->GetButtonUp(DOWN)) {
        printf("DOWN ");
    }
    if (keyboard->GetButton(UP) || keyboard->GetButton(DOWN) || keyboard2->GetButtonDown(UP) || keyboard2->GetButtonDown(DOWN)) {
        printf("Button ");
    }

    _hero->Update(elapsedSeconds);
    _hero2->Update(elapsedSeconds);

    
    
    PP1 = new Texture(_hero->_points, 1, _renderer);
    PP2 = new Texture(_hero2->_points, 2, _renderer);
}

void Game::Render() {
    SDL_RenderClear(_renderer);

    // renderizar imagenes, etc.
    _logoTexture->Render(&_destLogoRect, 0);

    
    _livesRect1.x = 75;
    _livesRect1.y = 550;
    _livesRect1.w = 80;
    _livesRect1.h = 20;

    for (int i = 0; i < livesP1.size(); i++) {
        livesP1.at(i)->Render(&_livesRect1, 0);
        _livesRect1.x += 90;
    }
      

    _livesRect2.x = 459;
    _livesRect2.y = 550;
    _livesRect2.w = 80;
    _livesRect2.h = 20;

    for (int i = 0; i < livesP2.size(); i++) {
        livesP2.at(i)->Render(&_livesRect2, 0);
        _livesRect2.x += 90;
    }

    _destPP1Rect.w = PP1->widthPP*4;
    _destPP1Rect.h = PP1->heigthPP*4;
    _destPP2Rect.w = PP2->widthPP*4;
    _destPP2Rect.h = PP2->heigthPP*4;


    PP1->Render(&_destPP1Rect, 0);
    PP2->Render(&_destPP2Rect, 0);
    _hero->Render();
    _hero2->Render();
    _map->Render();


    
    SDL_RenderPresent(_renderer);

    delete PP1;
    delete PP2;

    
}

void Game::Release() {
    _hero->Release();
    _hero2->Release();
    _logoTexture->Release();
    

    delete _hero;
    delete _hero2,
    delete _logoTexture;
    delete keyboard;
    delete keyboard2;
    delete _inputHandler;
    

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Game::IsRunning() {
    return _isRunning;
}

