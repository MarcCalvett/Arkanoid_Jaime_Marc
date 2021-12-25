#ifndef SDLPROJECT_TEXTURE_H
#define SDLPROJECT_TEXTURE_H

#pragma once
#include <string>
#include <SDL_render.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture {
public:
    Texture(float points, int numberPlayer, SDL_Renderer* renderer);
    Texture(std::string path, SDL_Renderer* renderer, double angle);
    Texture(std::string path, SDL_Renderer* renderer, double angle, SDL_Rect sourceRect);

    void Init();
    void Release();

    void SetSourceRect(const SDL_Rect* rect);

    void Render(const SDL_Rect* destRect, double angle) const;
    void Render(const SDL_Rect* destRect, double angle, SDL_Rect sourceRect);
    
    int heigthPP;
    int widthPP;
private:
    std::string _path;
    SDL_Renderer* _renderer;
    SDL_Rect _sourceRect;    
   // SDL_Rect _sourceRectBrick;
    SDL_Texture* _texture;    
    double _angle;
    //SDL_Texture* _points;
};


#endif //SDLPROJECT_TEXTURE_H