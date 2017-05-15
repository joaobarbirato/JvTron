#ifndef MOTO_H
#define MOTO_H

using namespace std;
/*
	Cabeçalho da Fila
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fila.h"
#include <string>

class Moto{
    public:
        
        void mover();
        int getAuxX();
        int getAuxY();
        
        sf::Sprite getForma();
        void mudarCima();
        void mudarBaixo();
        void mudarEsquerda();
        void mudarDireita();
        
        void setPosicaoInicial(int,sf::Vector2f);
        void setCor(string);
        int posicao;
    private:
        Fila cauda;
        sf::Sprite forma;
        sf::Texture textura;
        int auxX;
        int auxY;
        string cor;
        
};

#endif 
// MOTO_H
