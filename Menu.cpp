#include "Menu.h"
#include <iostream>
using std::string;

Menu::Menu(float larg, float alt){
	string texto[maxNumeroItens] = {"Jogar", "Opcoes", "Sair"};
	largura = larg;
	altura = alt;
	if(!fonte.loadFromFile("TRON.TTF")){
		//error
	}
	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(20);

		if(i == 0)
			botao[i].setFillColor(sf::Color(0,255,255));
		else
			botao[i].setFillColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f((largura-100)/2.2, (altura-100)*2/3 + altura/(maxNumeroItens+1)/4*	i));
	}

	numeroItem = 0;
};
Menu::~Menu(){};

void Menu::desenha(sf::RenderWindow &janela){
	sf::Text titulo;
	titulo.setFont(fonte);
	titulo.setString("JvTron");
	titulo.setCharacterSize(50);
	titulo.setPosition(sf::Vector2f((largura-100)/2.8, altura/3 - 80));
	titulo.setFillColor(sf::Color(0,255,255));
	sf::Vertex vertEsq[] =	{
	    sf::Vertex(sf::Vector2f(50, altura/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(50, altura - 50), sf::Color(0,255,255))
	};
	sf::Vertex vertDir[] =	{
	    sf::Vertex(sf::Vector2f(largura - 50, altura/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), sf::Color(0,255,255))
	};
	sf::Vertex horCima[] =	{
	    sf::Vertex(sf::Vector2f(50, altura/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, altura/3), sf::Color(0,255,255))
	};
	sf::Vertex horBaixo[] =	{
	    sf::Vertex(sf::Vector2f(50, altura - 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), sf::Color(0,255,255))
	};

	janela.draw(titulo);
	for(int i = 0; i < maxNumeroItens; i++){
		janela.draw(botao[i]);
	}
	janela.draw(vertEsq, 2, sf::Lines);
	janela.draw(vertDir, 2, sf::Lines);
	janela.draw(horCima, 2, sf::Lines);
	janela.draw(horBaixo, 2, sf::Lines);
};

void Menu::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};

void Menu::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};
int Menu::ItemApertado(){ return numeroItem; };