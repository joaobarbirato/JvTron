#include <iostream>

#include <SFML/Graphics.hpp>

class Disco{
private:
	float posx;
	float posy;
public:
	Disco();
	void aparece(float x, float y, sf::RenderWindow & App);
	float getx() const;
	float gety() const;
};

Disco::Disco(){};

void Disco::aparece(float x, float y, sf::RenderWindow & App){
	sf::Texture tDisco;
	sf::Sprite sDisco;
	tDisco.loadFromFile("imagens/disk.png");
	sDisco.setTexture(tDisco);
	sDisco.move(x,y);
	posx = x;
	posy = y;
	App.draw(sDisco);
};
float Disco::getx() const{return posx;};
float Disco::gety() const{return posy;};