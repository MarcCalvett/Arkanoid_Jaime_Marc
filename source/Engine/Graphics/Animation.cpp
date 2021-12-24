#include "Animation.h"
#include <utility>
#include "Texture.h"

Animation::Animation(std::string path, SDL_Renderer* renderer, double angle, SDL_Rect sourceRect) : _angle(angle), 
    _sourceRect(sourceRect)
{

    _texture = new Texture(std::move(path), renderer, _angle, _sourceRect);

}

void Animation::Init() {

    _texture->Init();
    /*_sourceRect.w = _frameWidth;
    _sourceRect.h = _frameHeight;*/
    
}

void Animation::Update(double elapsedSeconds) {
    _currentTime += elapsedSeconds;

    if (_currentTime > _duration) {
        _currentTime -= _duration;
    }

    //auto frameIndex = int(_currentTime / _duration * 10);

    //_sourceRect.x = frameIndex * _frameWidth;
    //_texture->SetSourceRect(&_sourceRect);
}

void Animation::Render(const SDL_Rect* destRect) const {
    _texture->Render(destRect, _angle);
}

void Animation::Render(const SDL_Rect* destRect,SDL_Rect sourceRect) {
    _texture->Render(destRect, _angle, _sourceRect);
}

void Animation::Release() {
    _texture->Release();
    delete _texture;
}
