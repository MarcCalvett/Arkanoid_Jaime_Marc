#pragma once
#include <SDL_render.h>
#include "Engine/Graphics/Animation.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Input/Controller.h"

//class Texture;
//class Animation;
//class Controller;

enum class BrickType { N,H,F };


class Brick
{
public:
    Brick();
    Brick(SDL_Renderer* renderer, double angle, int destBrickRectX, int destBrickRectY, int destBrickRectW, int destBrickRectH, int brickXPos, BrickType type);
    void Init();
    void Release();

    void Update(double elapsedSeconds);

    void Render();

    void SetMaxMinToBreakN(int& minHitsToBreak, int& maxHitsToBreak);
    void SetMaxMinToBreakH(int& minHitsToBreak, int& maxHitsToBreak);
    bool Print;


private:
	BrickType _type;
    int _minHitsToBreak;
    int _maxHitsToBreak;
    SDL_Renderer* _renderer; 
    Animation* _brickAnimation;
    SDL_Rect _destBrickRect;
    float _brickXPosition;
    double _angle;
    SDL_Rect _sourceRect;
    bool isBreak;

};

