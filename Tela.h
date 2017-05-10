#ifndef TELA_H
#include <SFML/Graphics.hpp>

class Tela{
private:
	float largura, altura, centrox, centroy;
	float tamanhoFonte;
	sf::Font fonte;
	sf::Text titulo;
public:
	Tela(float, float, float);
	~Tela();

	virtual void desenha(sf::RenderWindow * janela) const = 0;
	float getTFonte() const;
	float getLargura() const;
	float getAltura() const;
	float getCx() const;
	float getCy() const;
	sf::Font getFonte() const;
	sf::Text getTitulo() const;
};

#endif