#ifndef SDLPROJECT_TEXTURE_H
#define SDLPROJECT_TEXTURE_H


#include <string>
#include <SDL_render.h>

class Texture {
public:
    Texture(std::string path, SDL_Renderer* renderer, double angle);

    void Init();
    void Release();

    void SetSourceRect(const SDL_Rect* rect);

    void Render(const SDL_Rect* destRect, double angle) const;

private:
    std::string _path;
    SDL_Renderer* _renderer;
    SDL_Rect _sourceRect;    
    SDL_Texture* _texture;    
    double _angle;
};


#endif //SDLPROJECT_TEXTURE_H