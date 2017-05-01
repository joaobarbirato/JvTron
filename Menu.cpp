#include "Menu.h"
#include <iostream>
using std::string;

Menu::Menu(float largura, float altura){
	string texto[maxNumeroItens] = {"Jogar", "Opcoes", "Sair"};
	if(!fonte.loadFromFile("/usr/share/fonts/TTF/DejaVuSansMono.ttf")){
		//error
	}
	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(fonte);

		if(i == 0)
			botao[i].setFillColor(sf::Color::Red);
		else
			botao[i].setFillColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(largura/2, altura/(maxNumeroItens+1)*i));
	}

	numeroItem = 0;
};
Menu::~Menu(){};

void Menu::desenha(sf::RenderWindow &janela){
	for(int i = 0; i < maxNumeroItens; i++){
		janela.draw(botao[i]);
	}
};

void Menu::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setFillColor(sf::Color::Red);
	}
};

void Menu::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setFillColor(sf::Color::Red);
	}
};
int Menu::ItemApertado(){ return numeroItem; };