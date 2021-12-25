#include "Engine/Graphics/Animation.h"
#include "Engine/Input/Controller.h"
#include "Hero.h"
#include <iostream>

const int UP = 1;
const int DOWN = 2;

Hero::Hero(SDL_Renderer* renderer, Controller* controller, double angle, int destHeroRectX, int destHeroRectY, int destHeroRectW, int destHeroRectH, int heroXPos
) : _renderer(renderer), _controller(controller), _angle(angle) {

    _points = 0;

    _destHeroRect.x = destHeroRectX;
    _destHeroRect.y = destHeroRectY;
    _destHeroRect.w = destHeroRectW;
    _destHeroRect.h = destHeroRectH;

    _heroXPosition = heroXPos;
}

void Hero::Init() {

    
    sourceRect.w = 60;
    sourceRect.h = 20;
    _heroAnimation = new Animation("resources/platform.png", _renderer,_angle,sourceRect);  

   _heroAnimation->Init();
   /*
    _destHeroRect.x = 10;
    _destHeroRect.y = 300;
    _destHeroRect.w = 80;
    _destHeroRect.h = 20;

    _heroXPosition = 0;*/
}

void Hero::Update(double elapsedSeconds) {
    if (_controller->GetButtonDown(DOWN) && _destHeroRect.y < 419) {
       // std::cout << "polla";
        _destHeroRect.y = _destHeroRect.y + 10000 * elapsedSeconds;
        if (_destHeroRect.y > 419) {
            _destHeroRect.y = 419;
        }
        if (_points > 0) {
            _points--;
        }
        //std::cout << _destHeroRect.y;
    }
    if (_controller->GetButtonDown(UP) && _destHeroRect.y > 60) {
        _destHeroRect.y = _destHeroRect.y - 10000 * elapsedSeconds;
        if (_destHeroRect.y < 60) {
            _destHeroRect.y = 60;
        }
        _points++;
        
            
    }
   // _destHeroRect.x = _heroXPosition;
    
    //_heroAnimation->Update(elapsedSeconds);
}

void Hero::Render() {
    _heroAnimation->Render(&_destHeroRect);
}



void Hero::Release() {
    _heroAnimation->Release();
    delete _heroAnimation;
}



