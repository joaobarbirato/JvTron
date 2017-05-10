#include "Menu.h"
#include <iostream>
using std::string;

Menu::Menu(float larg, float alt): Tela::Tela(larg, alt, 50), maxNumeroItens(3) {
	string texto[maxNumeroItens] = {"Jogar", "Opcoes", "Sair"};
	botao = new sf::Text[maxNumeroItens];
/*	getLargura() = larg;
	getAltura() = alt;
	getCx() = getLargura()/2;
	getCy() = getAltura()/2;
	if(!fonte.loadFromFile("TRON.TTF")){
		//error
	}*/
	getTitulo().setCharacterSize(getTFonte());
	getTitulo().setPosition(sf::Vector2f(getCx() - getTitulo().getCharacterSize()*3, getCy()-getAltura()*1/3 + getTitulo().getCharacterSize()));
	getTitulo().setFillColor(sf::Color(0,255,255));

	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(getFonte());
		botao[i].setCharacterSize(20);

		if(i == 0)
			botao[i].setFillColor(sf::Color(0,255,255));
		else
			botao[i].setFillColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(getCx() - botao[i].getCharacterSize()*3, (getAltura()-100)*2/3 + getAltura()/(maxNumeroItens+1)/4*	i));
	}

	numeroItem = 0;
};
Menu::~Menu(){
	delete [] botao;
};

void Menu::desenha(sf::RenderWindow *janela) const{
	sf::Vertex vertEsq[] =	{
	    sf::Vertex(sf::Vector2f(50, getAltura()/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(50, getAltura() - 50), sf::Color(0,255,255))
	};
	sf::Vertex vertDir[] =	{
	    sf::Vertex(sf::Vector2f(getLargura() - 50, getAltura()/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(getLargura() - 50, getAltura() - 50), sf::Color(0,255,255))
	};
	sf::Vertex horCima[] =	{
	    sf::Vertex(sf::Vector2f(50, getAltura()/3), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(getLargura() - 50, getAltura()/3), sf::Color(0,255,255))
	};
	sf::Vertex horBaixo[] =	{
	    sf::Vertex(sf::Vector2f(50, getAltura() - 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(getLargura() - 50, getAltura() - 50), sf::Color(0,255,255))
	};

	janela->draw(getTitulo());
	for(int i = 0; i < maxNumeroItens; i++){
		janela->draw(botao[i]);
	}
	janela->draw(vertEsq, 2, sf::Lines);
	janela->draw(vertDir, 2, sf::Lines);
	janela->draw(horCima, 2, sf::Lines);
	janela->draw(horBaixo, 2, sf::Lines);
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

sf::Vector2f Menu::getCentro() const{
	return sf::Vector2f(getCx(),getCy());
};