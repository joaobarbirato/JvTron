#ifndef MOTO_H
#define MOTO_H

using namespace std;

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
	void RetiraAPartirDe(const int &, bool &);
	bool Vazia() const;
};

#endif

class moto{
    public:
        moto(int j, string n, char c);
        void movimento();
        void estatico();
        //void bateu();

    private:
        string nome;
        int jogador;
        char cor;
        Fila cauda;
};

#endif // MOTO_H
