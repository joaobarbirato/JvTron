/*
    JvTron: Trabalho 1
    Departamento de Computa��o
    UFSCar Universidade Federal de S�o Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        Jo�o Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523

    Controle de Vers�o: https://github.com/joaobarbirato/JvTron
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "screens.hpp"

/* isso � o comando no terminal linux pra compilar o programa
g++ -c main.cpp && g++ main.o screens.hpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./sfml-app
*/

// main()
// Fun��o principal e gerenciadora de telas.
int main (){
    std::vector<Tela*> Screens; // vetor que conter� as telas
    int screen = 0; // tela de inicio da aplicacao (0) � o menu

    // Janela do aplicativo creation
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "JvTron", sf::Style::Titlebar | sf::Style::Close);

    // Esconder seta do mouse
    App.setMouseCursorVisible(false);

    //declara��o dos objetos sonoros
    sf::Music musica;

    // Preparacao das tela
    Menu * s0 = new Menu(App.getSize().x, App.getSize().y); // TELA 0: menu do jogo
    Screens.push_back(s0);
    Campo * s1 = new Campo(); // TELA 1: campo do jogo
    Screens.push_back(s1);
    Ganhou * s2 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(0, 255, 255)); // TELA 2: azul ganhou
    Screens.push_back(s2);
    Ganhou * s3 = new Ganhou(App.getSize().x, App.getSize().y, sf::Color(250, 60, 0)); // TELA 3: laranja ganhou
    Screens.push_back(s3);
    Regras * s4 = new Regras(App.getSize().x, App.getSize().y); // TELA 4: Regras do jogo
    Screens.push_back(s4);

    //verifica��es. Se der erro na abertura de uma musica, o programa retorna 1
    if(!musica.openFromFile("tron.ogg")){
        std::cout << "ERROR 1" << std::endl;
        return 1;
    }

    //music e entra num loop para que a musica reinicie quando ela acabar
    musica.setLoop(true);

    //inicializa a musica
    musica.play();

    // loop principal
    while (screen >= 0){
        if( (screen = Screens[screen]->Run(App)) == 1 )// chamada do metodo que faz funcionar a tela atual
            Screens[1] = new Campo();
    } // fim loop principal

    return EXIT_SUCCESS; // fim do programa
}
// fim main
