#include <SFML/Graphics.hpp>
#include <iostream>
#include "screens.hpp"
/*
g++ -c main.cpp && g++ main.o Tela.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

*/

int main (){
    //Applications variables
    std::vector<Tela*> Screens;
    int screen = 0;

    //Window creation
    sf::RenderWindow App(sf::VideoMode(800, 800, 32), "SFML Demo 3");

    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //Screens preparations
    Menu s0(App.getSize().x, App.getSize().y);
    Screens.push_back(&s0);
    Campo s1;
    Screens.push_back(&s1);
    Ganhou s2(App.getSize().x, App.getSize().y);
    Screens.push_back(&s2);
    Perdeu s3(App.getSize().x, App.getSize().y);
    //Main loop
    while (screen >= 0){
//        s2.Run(App);
        std::cout<<screen<<std::endl;
        screen = Screens[screen]->Run(App);
    }

    return EXIT_SUCCESS;
}