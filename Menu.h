#ifndef MENU_H

#include <SFML/Graphics.hpp>

#define maxNumeroItens 3

class Menu{
private:
	int numeroItem;
	sf::Font fonte;
	sf::Text botao[maxNumeroItens];
public:
	Menu(float largura, float altura);
	~Menu();

	void desenha(sf::RenderWindow &janela);
	void MovaParaCima();
	void MovaParaBaixo();
	int ItemApertado();
};

#endif