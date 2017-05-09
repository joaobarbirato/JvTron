#ifndef MENU_H

#include <SFML/Graphics.hpp>

#define maxNumeroItens 3

class Menu{
private:
	int numeroItem;
	float largura, altura, centrox, centroy;
	sf::Font fonte;
	sf::Text botao[maxNumeroItens];
public:
	Menu(float larg, float alt);
	~Menu();

	void desenha(sf::RenderWindow &janela);
	void MovaParaCima();
	void MovaParaBaixo();
	int ItemApertado();

	sf::Vector2f getCentro() const;
};

#endif