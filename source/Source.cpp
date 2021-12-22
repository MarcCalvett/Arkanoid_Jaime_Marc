#include <SDL.h>
#include <cstdio>
#include "Game.h"
#include <exception>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
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

    /*std::cout << "Nombre de la raíz: " << doc.first_node()->name() << "\n";
    std::cout << "Value: " << (std::string)doc.first_node()->value() << "\n";*/

    rapidxml::xml_node<>* pRoot = doc.first_node();
        
    rapidxml::xml_attribute<>* pattr;

    rapidxml::xml_node<>* pNodee = pRoot->first_node("BrickInfo");

    rapidxml::xml_node<>* pNodeII = pNodee->first_node();

    std::cout<<"Game" <<"\n";

    std::cout << "    " << pNodee->name()<< "\n";
    
    std::cout << "        Normal " << pNodeII->first_attribute()->name() << " = " << pNodeII->first_attribute()->value() << "  "; //aixo es el valor de min

    std::cout << "        Normal " << pNodeII->last_attribute()->name() << " = " << pNodeII->last_attribute()->value() << "\n";

    pNodeII = pNodeII->next_sibling();

    std::cout << "        Heavy " << pNodeII->first_attribute()->name() << " = " << pNodeII->first_attribute()->value() << "  "; //aixo es el valor de min

    std::cout << "        Heavy " << pNodeII->last_attribute()->name() << " = " << pNodeII->last_attribute()->value() << "\n";

    
    for (rapidxml::xml_node<>* pNode = pRoot->first_node("Level"); pNode; pNode = pNode->next_sibling()) {


        //std::cout << "this should say something\n";
        std::cout << pNode->name();
        std::cout << '\n';


        for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
                   
            std::cout << "      " << pNodeI->name() << " : "; //this says the type of block and follows up with : always says brick

            std::cout << "i = " << pNodeI->first_attribute()->value() << "  "; //aixo es el valor de i

            pattr = pNodeI->first_attribute();
            pattr++;
            
            std::cout << "j = " << pattr->value(); //aixo es el valor de j

            std::cout << " type = " << pNodeI->last_attribute()->value() << "\n"; //aixo es el type de brick

        }
        
    }

    //for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling()) {


    //    std::cout << "this should say something\n";
    //    std::cout << pNode->name();
    //    std::cout << '\n';


    //    for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {






    //        std::cout << "      " << pNodeI->name() << " : "; //this says the type of block and follows up with : always says brick

    //        std::cout << "i = " << pNodeI->first_attribute()->value() << "  "; //aixo es el valor de i

    //        pattr = pNodeI->first_attribute();
    //        pattr++;

    //        std::cout << "j = " << pattr->value(); //aixo es el valor de j

    //        std::cout << " type = " << pNodeI->last_attribute()->value() << "\n"; //aixo es el type de brick

    //    }

    //}
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