#include <iostream>
#include "Moto.h"

using namespace std;

/*
	Implementação dos métodos da Fila
*/

void Moto::mudarCima(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("cima.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().x)/2 ,forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().x)/2  , forma.getPosition().y + forma.getTexture()->getSize().y -  (auxMoto.getTexture()->getSize().y)/2) );
    }
    auxX=0;
    auxY=(auxMoto.getTexture()->getSize().y)/2;
    forma.setTexture(textura);
    forma.setPosition(auxMoto.getPosition());
    posicao=0;
};
void Moto::mudarBaixo(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("baixo.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 0){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x - (auxMoto.getTexture()->getSize().x)/2  ,forma.getPosition().y + (forma.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 2){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + forma.getTexture()->getSize().x - (auxMoto.getTexture()->getSize().x)/2  , forma.getPosition().y + (forma.getTexture()->getSize().y)/2 ));
    }
    auxX= (auxMoto.getTexture()->getSize().x)/2;
    auxY=0;
    forma.setTexture(textura);
    forma.setPosition(auxMoto.getPosition());
    posicao=3;
};
void Moto::mudarDireita(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/direita.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().x)/2 ,forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().x)/2  , forma.getPosition().y + forma.getTexture()->getSize().y - (auxMoto.getTexture()->getSize().y)/2) );
    }
    auxX=0;
    auxY=(auxMoto.getTexture()->getSize().y)/2;
    forma.setTexture(textura);
    forma.setPosition(auxMoto.getPosition());
    posicao=0;
    
};
void Moto::mudarEsquerda(){
    sf::Texture textura;
    sf::Sprite auxMoto;
    
    textura.loadFromFile("motoMovendo/esquerda.png");
    auxMoto.setTexture(textura);
    
    if(posicao == 1){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x  + (forma.getTexture()->getSize().x)/2 - auxMoto.getTexture()->getSize().x   ,forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 + forma.getTexture()->getSize().y  ));
    }
    if(posicao == 3){
        auxMoto.setPosition(sf::Vector2f(forma.getPosition().x - auxMoto.getTexture()->getSize().x + (forma.getTexture()->getSize().x)/2   , forma.getPosition().y - (auxMoto.getTexture()->getSize().y)/2 ));
    }
    auxX=auxMoto.getTexture()->getSize().x;
    auxY=(auxMoto.getTexture()->getSize().y)/2;
    forma.setTexture(textura);
    forma.setPosition(auxMoto.getPosition());
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
 Fila Moto::getCauda(){
     
     return cauda;
};

int Moto::getAuxX(){
    
    return auxX;
};
int Moto::getAuxY(){
    
    return auxY;
};

void Moto::adicionarCauda(){
    sf::Vertex auxCauda;
    bool ok;
    auxCauda.position=forma.getPosition();
    auxCauda.position.y+=auxY;
    auxCauda.position.x+=auxX;
    auxCauda.color = sf::Color(0,255,255);
    cauda.Insere(auxCauda,ok);
    
};

sf::Sprite Moto::getForma(){
    
    return forma;
}

