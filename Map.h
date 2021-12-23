#pragma once
#include <vector>
#include <iostream>
#include <SDL_render.h>
#include "source/Brick.h"



class Texture;
class Animation;
class Controller;


class Map
{
public:
	void Init();
	void Update();
	void Render();
	BrickType CharToBrick(char a);
private:
	Brick* map[11][12];
	SDL_Renderer* _renderer;
};

