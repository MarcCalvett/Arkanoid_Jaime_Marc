#include <SDL_image.h>

#include <assert.h>
#include <utility>
#include "Texture.h"

Texture::Texture(std::string path, SDL_Renderer* renderer, double angle) : _path(std::move(path)),
_renderer(renderer),
_sourceRect(),
_texture(nullptr),_angle(angle){

    /*centerPoint->x = 0;
    centerPoint->y = 0;*/
    
}


Texture::Texture(std::string path, SDL_Renderer* renderer, double angle, SDL_Rect sourceRect) : _path(std::move(path)),
_renderer(renderer),
_sourceRect(sourceRect),
_texture(nullptr), _angle(angle) {

    /*centerPoint->x = 0;
    centerPoint->y = 0;*/

}

void Texture::Init() {
    SDL_Surface* surfaceTemp = IMG_Load(_path.c_str());
    _texture = SDL_CreateTextureFromSurface(_renderer, surfaceTemp);
    if (_sourceRect.w == 0 && _sourceRect.h == 0) {
        SDL_QueryTexture(_texture, nullptr, nullptr, &_sourceRect.w, &_sourceRect.h);
    }    
    SDL_FreeSurface(surfaceTemp);
    
}

void Texture::SetSourceRect(const SDL_Rect* rect) {
    _sourceRect.x = rect->x;
    _sourceRect.x = rect->x;
    _sourceRect.w = rect->w;
    _sourceRect.h = rect->h;
    
    
    
}

void Texture::Render(const SDL_Rect* destRect, double angle) const {
    assert(_texture != nullptr && "Texture is not initialized, try to call to Init first");

    SDL_RenderCopyEx(_renderer, _texture, &_sourceRect, destRect, angle,NULL,SDL_FLIP_NONE);
}

void Texture::Render(const SDL_Rect* destRect, double angle, SDL_Rect sourceRect)  {
    assert(_texture != nullptr && "Texture is not initialized, try to call to Init first");

    _sourceRect.h = sourceRect.h;
    _sourceRect.w = sourceRect.w;
    _sourceRect.x = sourceRect.x;
    _sourceRect.y = sourceRect.y;

    SDL_RenderCopyEx(_renderer, _texture, &_sourceRect, destRect, angle, NULL, SDL_FLIP_NONE);
}

void Texture::Release() {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
}

