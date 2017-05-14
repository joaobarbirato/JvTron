#ifndef MOTO_H
#define MOTO_H

using namespace std;
/*
	Cabeçalho da Fila
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fila.h"


class Moto{
    public:
        
        void moverCima();
        void moverBaixo();
        void moverEsquerda();
        void moverDireita();
        int getAuxX();
        int getAuxY();
        
        sf::Sprite getForma();
        void mudarCima();
        void mudarBaixo();
        void mudarEsquerda();
        void mudarDireita();
        
        void setPosicao(int);
        

    private:
        Fila cauda;
        sf::Sprite forma;
        sf::Texture textura;
        int auxX;
        int auxY;
        int posicao;
        
};

#endif 
// MOTO_H
