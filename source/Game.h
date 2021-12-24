#pragma once
#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H
#include <vector>
#include "Map.h"

class Texture;
class Hero;
class InputHandler;
class map;

class Game {
public:
    void Init();

    void HandleEvents();

    void Update(double elapsedSeconds);

    void Render();

    void Release();

    bool IsRunning();

private:
    void InitSDL();

    void CreateWindowAndRender();

private:
    bool _isRunning;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    Texture* _logoTexture;
    SDL_Rect _destLogoRect;
    SDL_Rect _livesRect1;
    SDL_Rect _livesRect2;
    SDL_Point point;
    std::vector<Texture*>livesP1;
    std::vector<Texture*>livesP2;
      

    Hero* _hero;
    Hero* _hero2;
    Map* _map;

    InputHandler* _inputHandler;
};


#endif //SDLPROJECT_GAME_H


