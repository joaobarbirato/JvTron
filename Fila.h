#ifndef FILA_H
/*
	Cabeçalho da Fila
*/
#include <iostream>

// Estrutura do nó
struct Node{
	char info;
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
	void Insere(const char &, bool &);
	void Retira(char &, bool &);
	bool Vazia() const;
};

#endif