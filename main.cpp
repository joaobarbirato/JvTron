#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "screens.hpp"
/*
g++ -c main.cpp && g++ main.o screens.hpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
*/

using namespace std;

int main (){
    //Applications variables
    std::vector<Tela*> Screens;
    int screen = 0;

    //Window creation
    sf::RenderWindow App(sf::VideoMode(800, 800, 32), "SFML Demo 3");

    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //declaração dos objetos sonoros
    sf::Music music;
    sf::Music som1;
    sf::Music som2;

    //verificações. Se der erro na abertura de uma musica, o programa retorna 1
    if(!music.openFromFile("tron.ogg")){
        cout << "ERROR 1" << endl;
        return 1;
    }

    if(!som1.openFromFile("som-moto1.ogg")){
        cout << "ERROR 2" << endl;
        return 1;
    }

    if(!som2.openFromFile("som-moto2.ogg")){
        cout << "ERROR 2" << endl;
        return 1;
    }

    //altera o volume do som1 para 40 e som2 para 60, o maximo é 100
    som1.setVolume(40);
    som2.setVolume(60);

    //music e som2 entram num loop para que as musicas reiniciem quando elas acabarem
    music.setLoop(true);
    som2.setLoop(true);

    //inicializa as musicas
 //   music.play();
 //   som1.play();
 //   som2.play();

    //Screens preparations
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y);
    Screens.push_back(s0);
    Campo * s1 = new Campo;
    Screens.push_back(s1);
    Ganhou * s2 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(0, 255, 255));
    Screens.push_back(s2);
    Ganhou * s3 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(250, 60, 0));
    Screens.push_back(s3);
    Regras * s4 = new Regras(App.getSize().x, App.getSize().y);
    Screens.push_back(s4);
    //Main loop
    while (screen >= 0){
        std::cout<<screen<<std::endl;
        screen = Screens[screen]->Run(App);
    }
    return EXIT_SUCCESS;
}
