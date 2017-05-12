#include <iostream>
#include "moto.h"
using namespace std;

/*
	Implementação dos métodos da Fila
*/
Moto::moto()
{
    
}

void Moto::mudarCima(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/cima.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2 ,moto.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2  , moto.getPosition().y + moto.getTexture()->getSize().y -  (auxMoto.getTexture()->getSize().y)/2) );
    }
    this->auxX=0;
    this->auxY=(auxMoto.getTexture()->getSize().y)/2;
    this->setTexture(auxMoto.getTexture());
    this->setPosition(auxMoto.getPosition());
    posicao=0;
};
void Moto::mudarBaixo(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/baixo.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 0){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x - (auxMoto.getTexture()->getSize().x)/2  ,moto.getPosition().y + (moto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 2){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x + moto.getTexture()->getSize().x - (auxMoto.getTexture()->getSize().x)/2  , moto.getPosition().y + (moto.getTexture()->getSize().y)/2 ));
    }
    this->auxX= (auxMoto.getTexture()->getSize().x)/2;
    this->auxY=0;
    this->setTexture(auxMoto.getTexture());
    this->setPosition(auxMoto.getPosition());
    posicao=3;
};
void Moto::mudarDireita(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/direita.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2 ,moto.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2  , moto.getPosition().y + moto.getTexture()->getSize().y - (auxMoto.getTexture()->getSize().y)/2) );
    }
    this->auxX=0;
    this->auxY=(auxMoto.getTexture()->getSize().y)/2;
    this->setTexture(auxMoto.getTexture());
    this->setPosition(auxMoto.getPosition());
    posicao=0;
    
};
void Moto::mudarEsquerda(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/esquerda.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x  + (moto.getTexture()->getSize().x)/2 - auxMoto.getTexture()->getSize().x   ,moto.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 + moto.getTexture()->getSize().y  ));
    }
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(moto.getPosition().x - auxMoto.getTexture()->getSize().x + (moto.getTexture()->getSize().x)/2   , moto.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    this->auxX=auxMoto.getTexture()->getSize().x;
    this->auxY=(auxMoto.getTexture()->getSize().y)/2;
    this->setTexture(auxMoto.getTexture());
    this->setPosition(auxMoto.getPosition());
    posicao=2;
    
    
};

void Moto::moverCima(){
    this->move(0.0f,-1.0f); 
    this->adicionarCauda();
};
void Moto::moverBaixo(){
    this->move(0.0f,1.0f); 
    this->adicionarCauda();
};
void Moto::moverEsquerda(){
    this->move(-1.0f,0.0f);
    this->adicionarCauda();
};
void Moto::moverDireita(){
    this->move(1.0f,0.0f);
    this->adicionarCauda();
};


void Moto::adicionarCauda(){
    sf::Vertex auxCauda;
    bool ok;
    auxCauda.position=this->getPosition();
    auxCauda.position.y+=auxY;
    auxCauda.position.x+=aux;
    auxCauda.color = sf::Color(0,255,255);
    this->cauda.Insere(auxCauda,ok);
    
};

