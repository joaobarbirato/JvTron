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
            
        sf::Sprite getForma();
        void mudarCima();
        void mudarBaixo();
        void mudarEsquerda();
        void mudarDireita();
        
        Fila getCauda();

    private:
        Fila cauda;
        sf::Sprite forma;
        int auxX;
        int auxY;
        int posicao;
        void adicionarCauda();
        
};

#endif 
// MOTO_H
