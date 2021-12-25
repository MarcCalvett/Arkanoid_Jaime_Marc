#include "Brick.h"
//#include "Engine/Graphics/Animation.h"
//#include <iostream>
#include "../dependencies/XML/rapidxml.hpp"
#include "../dependencies/XML/rapidxml_utils.hpp"
#include "../dependencies/XML/rapidxml_iterators.hpp"
#include "../dependencies/XML/rapidxml_print.hpp"
#include <sstream>

Brick::Brick()
{
    Print = false;
}

Brick::Brick(SDL_Renderer* renderer, double angle, int destBrickRectX, int destBrickRectY, int destBrickRectW, int destBrickRectH, int brickXPos, BrickType type)
	: _renderer(renderer), _angle(angle), _type(type)
{
    Print = true;
    _destBrickRect.x = destBrickRectX;
    _destBrickRect.y = destBrickRectY;
    _destBrickRect.w = 40;
    _destBrickRect.h = 20;

   // _brickXPosition = brickXPos;

    switch (_type)
    {
    case BrickType::F:
        _sourceRect.x = 0;
        _sourceRect.y = 40;
        Init();
       // _brickAnimation->Init(_sourceRect.x, _sourceRect.y);
        break;
    case BrickType::N:
        _sourceRect.x = 0;
        _sourceRect.y = 0;
        Init();
        //_brickAnimation->Init(_sourceRect.x, _sourceRect.y);
        SetMaxMinToBreakN(_minHitsToBreak,_maxHitsToBreak);        
        break;
    case BrickType::H:
        _sourceRect.x = 0;
        _sourceRect.y = 20;
        Init();
        //_brickAnimation->Init(_sourceRect.x, _sourceRect.y);
        SetMaxMinToBreakH(_minHitsToBreak, _maxHitsToBreak);
        break;
    default:
        break;
    }
}

void Brick::Init()
{
    //_brickAnimation = new Animation("resources/platform.png", _renderer, 10, 1, 707, 587, _angle);

    _sourceRect.w = 40;
    _sourceRect.h = 20;
    _brickAnimation = new Animation("resources/bricks.jpg", _renderer, _angle,_sourceRect);

    _brickAnimation->Init();
    //Render();
}

void Brick::Update(double elapsedSeconds)
{
    //_brickAnimation->SetSourceRect()
}

void Brick::SetMaxMinToBreakN(int& minHitsToBreak, int& maxHitsToBreak)
{
    rapidxml::xml_document<> doc;
    std::ifstream file("resources/config.xml"); 
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);


    rapidxml::xml_node<>* pRoot = doc.first_node();    
    rapidxml::xml_node<>* pNodee = pRoot->first_node("BrickInfo");
    rapidxml::xml_node<>* pNodeII = pNodee->first_node(); 

    

   char* minHits = pNodeII->first_attribute()->value(); //aixo es el valor de min
   char* maxHits = pNodeII->last_attribute()->value(); //aixo es el valor de max

   minHitsToBreak = *minHits - 48;
   maxHitsToBreak = *maxHits - 48;

   return;

}

void Brick::SetMaxMinToBreakH(int& minHitsToBreak, int& maxHitsToBreak)
{
    rapidxml::xml_document<> doc;
    std::ifstream file("resources/config.xml");
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);


    rapidxml::xml_node<>* pRoot = doc.first_node();    
    rapidxml::xml_node<>* pNodee = pRoot->first_node("BrickInfo");
    rapidxml::xml_node<>* pNodeII = pNodee->first_node();

    pNodeII = pNodeII->next_sibling();

    char* minHits = pNodeII->first_attribute()->value(); //aixo es el valor de min
    char* maxHits = pNodeII->last_attribute()->value(); //aixo es el valor de max

    minHitsToBreak = *minHits - 48;
    maxHitsToBreak = *maxHits - 48;

    return;
}

void Brick::Release()
{
    _brickAnimation->Release();
    delete _brickAnimation;
}

void Brick::Render() {
    _brickAnimation->Render(&_destBrickRect);
}
