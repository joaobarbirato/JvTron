#ifndef MOTO_H
#define MOTO_H

using namespace std;
/*
	Cabeçalho da Fila
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fila.h"


class Moto : sf::Sprite {
    public:
        moto();
        void moverCima();
        void moverBaixo();
        void moverEsquerda();
        void moverDireita();
        
        void mudarCima();
        void mudarBaixo();
        void mudarEsquerda();
        void mudarDireita();

    private:
        Fila cauda;
        int auxX;
        int auxY;
        
        void adicionarCauda();
        
};

#endif 
// MOTO_H
