#ifndef MOTO_H
#define MOTO_H

using namespace std;
/*
	Cabeçalho da Fila
*/
#include <iostream>
#include "Fila.h"


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
