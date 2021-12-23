#include "Map.h"
//#include "Engine/Graphics/Animation.h"
#include <iostream>
#include "../dependencies/XML/rapidxml.hpp"
#include "../dependencies/XML/rapidxml_utils.hpp"
#include "../dependencies/XML/rapidxml_iterators.hpp"
#include "../dependencies/XML/rapidxml_print.hpp"
#include <sstream>


void Map::Init()
{
    //54.54H
    //27.27W
    //236.38 + 27.7 * j
    // 54.54 * i
    //Brick*fillMap = new Brick()

    
    int i;
    int j;
    BrickType type;
    char typeC;
    //type = static_cast<BrickType>(typeC);
    

    rapidxml::xml_document<> doc;
    std::ifstream file("resources/config.xml"); //"../../res/files/BookStore.xml");

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);

    /*std::cout << "Nombre de la raíz: " << doc.first_node()->name() << "\n";
    std::cout << "Value: " << (std::string)doc.first_node()->value() << "\n";*/

    rapidxml::xml_node<>* pRoot = doc.first_node();

    rapidxml::xml_attribute<>* pattr;

    rapidxml::xml_node<>* pNodee = pRoot->first_node("BrickInfo");

    rapidxml::xml_node<>* pNodeII = pNodee->first_node();

    for (rapidxml::xml_node<>* pNode = pRoot->first_node("Level"); pNode; pNode = pNode->next_sibling()) {


        //std::cout << "this should say something\n";
        std::cout << pNode->name();
        std::cout << '\n';


        for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {

            //std::cout << "      " << pNodeI->name() << " : "; //this says the type of block and follows up with : always says brick

            char* iC = pNodeI->first_attribute()->value(); //aixo es el valor de i
            i = *iC - 48;

            pattr = pNodeI->first_attribute();
            pattr++;

            char*jC = pattr->value(); //aixo es el valor de j
            j = *jC - 48;

           char*typeB = pNodeI->last_attribute()->value(); //aixo es el type de brick
           //int holder = *typeB;
           type = CharToBrick(*typeB);

           map[i][j] = new Brick(_renderer, 90, (236.38 + 27.7 * j), 54.54 * i, 27.27, 54.54, 0, type);
           map[i][j]->Render();
        }

    }
}

void Map::Update()
{
}

void Map::Render()
{
}

BrickType Map::CharToBrick(char a)
{
    switch (a)
    {
    case 'N':
        return BrickType::N;
        break;

    case 'H':
        return BrickType::H;
        break;

    case 'F':
        return BrickType::F;
        break;

    default:
        break;
    }

    return BrickType::F;
}
