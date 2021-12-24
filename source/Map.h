#pragma once
#include <vector>
#include <iostream>
#include <SDL_render.h>
#include "Brick.h"



class Texture;
class Animation;
class Controller;


class Map
{
public:
	Map(SDL_Renderer*renderer);
	void Init();
	void Update();
	void Render();
	BrickType CharToBrick(char a);
private:
	Brick map[11][12];
	SDL_Renderer* _renderer;
};

