#ifndef FILA_H
/*
	Cabeçalho da Fila
*/

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da fila
class Fila{
private:
	int primeiro;
	int ultimo;
	int nElementos;
    sf::Vertex elementos[20000];
public:
	Fila();
	~Fila();
	void Insere( sf::Vertex &, bool &);
	void Retira(sf::Vertex  &, bool &);
	void RetiraAteElemento(sf::Vertex & x, bool & deuCerto);
	bool Vazia() const;
    bool Cheia() const;
    sf::Vertex* getDesenhoRastro();
};

#endif
