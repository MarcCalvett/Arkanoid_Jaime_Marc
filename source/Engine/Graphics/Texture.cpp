#include <SDL_image.h>

#include <assert.h>
#include <utility>
#include "Texture.h"
#include <string>
#include <sstream>


Texture::Texture(float points,int numberPlayer, SDL_Renderer* renderer):_renderer(renderer),_angle(0)
{
    
    
    TTF_Font* Sans = TTF_OpenFont("resources/Game_Over.ttf",24); //this opens a font style and sets a size
      
       // if (TTF_Init() != 0) throw"No es pot inicialitzar SDL_ttf";
   // TTF_Init();
    
    std::stringstream PP;
    PP << "PP" << numberPlayer << ": " << points;

    SDL_Color Red = { 255, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans , PP.str().c_str(), Red); // as TTF_RenderText_Solid could only be used on S

    

    _texture = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

    SDL_QueryTexture(_texture, nullptr, nullptr, &_sourceRect.w, &_sourceRect.h);
    heigthPP = _sourceRect.h;
    widthPP = _sourceRect.w;
    _sourceRect.x = 0;
    _sourceRect.y = 0;
    
    SDL_FreeSurface(surfaceMessage);
}

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

