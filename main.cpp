#include <SFML/Graphics.hpp>
#include <iostream>
#include "screens.hpp"
/*
g++ -c main.cpp && g++ main.o screens.hpp Moto.cpp Fila.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

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
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y);
    Screens.push_back(s0);
    Campo * s1 = new Campo;
    Screens.push_back(s1);
    Ganhou * s2 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(0, 255, 255));
    Screens.push_back(s2);
    Ganhou * s3 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(250, 110, 40));
    Screens.push_back(s3);
    Regras * s4 = new Regras(App.getSize().x, App.getSize().y, sf::Color(0, 255, 255));
    Screens.push_back(s4);
    //Main loop
    while (screen >= 0){
        std::cout<<screen<<std::endl;
        screen = Screens[screen]->Run(App);
    }
    return EXIT_SUCCESS;
}