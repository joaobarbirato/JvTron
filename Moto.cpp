#include <iostream>
#include "Moto.h"

using namespace std;

/*
	Implementação dos métodos da Fila
*/

void Moto::mudarCima(){
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/cima.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 0){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x - (forma.getTexture()->getSize().x)/2    ,forma.getPosition().y - auxMoto.getTexture()->getSize().y + forma.getTexture()->getSize().x/2  ));
    }
    if(posicao == 2){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + forma.getTexture()->getSize().y - auxMoto.getTexture()->getSize().x/2 , forma.getPosition().y + forma.getTexture()->getSize().x/2 - auxMoto.getTexture()->getSize().y ) );
    }
    
    auxX=(auxMoto.getTexture()->getSize().x)/2;
    auxY=auxMoto.getTexture()->getSize().y;
    
    forma=auxMoto;
    posicao=1;
};
void Moto::mudarBaixo(){
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/baixo.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 0){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x - (auxMoto.getTexture()->getSize().x)/2  ,forma.getPosition().y + (forma.getTexture()->getSize().x)/2));
    }
    if(posicao == 2){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + forma.getTexture()->getSize().y - (auxMoto.getTexture()->getSize().x)/2  , forma.getPosition().y + (forma.getTexture()->getSize().x)/2 ));
    }
    
    
        auxX= (auxMoto.getTexture()->getSize().x)/2;
        auxY=0;
    
    forma=auxMoto;
    posicao=3;
};
void Moto::mudarDireita(){
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/direita.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().y)/2 ,forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().y)/2  , forma.getPosition().y + forma.getTexture()->getSize().x - (auxMoto.getTexture()->getSize().y)/2) );
    }
    
    
        auxX=0;
        auxY=(auxMoto.getTexture()->getSize().y)/2;
    
     forma=auxMoto;
    posicao=0;
    
};
void Moto::mudarEsquerda(){
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/esquerda.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x  + (forma.getTexture()->getSize().y)/2 - auxMoto.getTexture()->getSize().x   ,forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 + forma.getTexture()->getSize().x  ));
    }
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x - auxMoto.getTexture()->getSize().x + (forma.getTexture()->getSize().y)/2   , forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    

        auxX=auxMoto.getTexture()->getSize().x;
        auxY=(auxMoto.getTexture()->getSize().y)/2;
    
     forma=auxMoto;
    posicao=2;
    
    
};

void Moto::moverCima(){
    forma.move(0.0f,-1.0f); 
};
void Moto::moverBaixo(){
    forma.move(0.0f,1.0f); 
};
void Moto::moverEsquerda(){
    forma.move(-1.0f,0.0f);
};
void Moto::moverDireita(){
    forma.move(1.0f,0.0f);
};

int Moto::getAuxX(){
    
    return auxX;
};
int Moto::getAuxY(){
    
    return auxY;
};

sf::Sprite Moto::getForma(){
    
    return forma;
}

void Moto::setPosicao(int x){
    posicao=x;
    forma.setPosition(sf::Vector2f(60,70));
}
