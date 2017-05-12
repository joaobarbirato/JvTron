#ifndef FILA_H
/*
	Cabeçalho da Fila
*/

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura do nó
struct Node{
	sf::Vertex info;
	struct Node *next;
};
typedef struct Node * NodePtr;

// Estrutura da fila
class Fila{
private:
	NodePtr primeiro;
	NodePtr ultimo;
	int nElementos;
public:
	Fila();
	~Fila();
	void Insere(const sf::Vertex  &, bool &);
	void Retira(sf::Vertex  &, bool &);
	void RetiraAPartirDe(const int &, bool &);
	bool Vazia() const;
};

#endif
