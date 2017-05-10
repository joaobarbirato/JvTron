#ifndef MENU_H

#include <SFML/Graphics.hpp>
#include "Tela.h"

class Menu: public Tela{
private:
	const int maxNumeroItens;
	int numeroItem;
/*	float largura, altura, centrox, centroy;
	sf::Font fonte;*/
	sf::Text *botao;
public:
	Menu(float larg, float alt);
	~Menu();

	void desenha(sf::RenderWindow *janela) const;
	void MovaParaCima();
	void MovaParaBaixo();
	int ItemApertado();

	sf::Vector2f getCentro() const;
};

#endif