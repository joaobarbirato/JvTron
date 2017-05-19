#ifndef TELA_H
#define TELA_H

#include <SFML/Graphics.hpp>

class Tela{
public:
	virtual int Run (sf::RenderWindow & app) = 0;
};

#endif