#include <SDL.h>
#include <cstdio>
#include "Game.h"
#include <exception>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "../dependencies/XML/rapidxml.hpp"
#include "../dependencies/XML/rapidxml_utils.hpp"
#include "../dependencies/XML/rapidxml_iterators.hpp"
#include "../dependencies/XML/rapidxml_print.hpp"



int main(int argc, char* args[]) {



    rapidxml::xml_document<> doc;
    std::ifstream file("resources/config.xml"); //"../../res/files/BookStore.xml");

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);

    rapidxml::xml_node<>* pRoot = doc.first_node();

    char *value;
    char *brickType;

    for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling()) {

        std::cout << pNode->name();// << ': ' << '\n';
        std::cout << '\n';


        for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {

            std::cout << "    " << pNodeI->name() << ' : ';
            brickType = pNodeI->value();
            std::cout << *brickType;
            
            std::cout << "        " << pNodeI->first_attribute()->name();
            value = pNodeI->first_attribute()->value();// << ': ' << pNodeI->value();
            std::cout << static_cast<int>(*value);
            std::cout << '\n';

        }
        
    }

    /*std::cout << "Nombre de la raíz: " << doc.last_node()->name() << "\n";
    std::cout << "Value: " << doc.first_attribute()->name() << "\n";*/
    /*rapidxml::xml_attribute<>* pNode;*/
   
    //rapidxml::xml_node<>* pNode = pRoot->value();


    /*rapidxml::xml_node<>* pRoot = doc.first_node();

    rapidxml::xml_attribute<> *pAttr;*/

   /* pAttr = pRoot->first_attribute();
    std::cout << pAttr->name();
    */
    
    //pRoot++;
    
    /*pRoot++;
    pRoot++;
    pRoot = pRoot->next_sibling();
    std::cout<<pRoot->name();*/

    /*for (rapidxml::xml_node<>* pNode = pRoot->first_node("Game"); pNode; pNode = pNode->next_sibling()) {
        std::cout << pNode->name() << ':' << '\n';
        for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
            std::cout << pNodeI->name() << ':' << pNodeI->value() << '\n';

        }
    }*/

    


   

    auto game = Game();
    try {
        game.Init();

        auto lastTime = std::chrono::system_clock::now();
        while (game.IsRunning()) {
            auto current = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = current - lastTime;
            game.HandleEvents();

            game.Update(elapsedSeconds.count());

            game.Render();
            lastTime = current;
        }

        game.Release();
    }
    catch (std::exception& exception) {
        fprintf(stderr, "%s", exception.what());
        SDL_Quit();
        return -1;
    }

    return 0;
}