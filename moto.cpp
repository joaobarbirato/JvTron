#include <iostream>
#include "moto.h"
using namespace std;

/*
	Implementação dos métodos da Fila
*/
moto::moto(int j, string n, char c)
{
    jogador = j;
    cout << "eu sou o jogador numero " << jogador << endl;
    nome = n;
    cout << "meu nome eh " << nome << endl;
    cor = c;
    cout << "minha cor eh " << cor << endl;
}

void moto::movimento(){
    cout << "estou me movendo" << endl;
}

void moto::estatico(){
    cout << "estou parado" << endl;
}

/*void moto::bateu(){
    cauda.RetiraAPartirDe(const int &, bool &);
} */
