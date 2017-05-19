/*
    JvTron: Trabalho 1
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523
    
    Controle de Versão: https://github.com/joaobarbirato/JvTron
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fila.hpp"

// Estrutura da Moto
class Moto{
private: // atributos privados
    std::string cor; // nome da cor
    sf::Sprite forma;
    sf::Texture textura;
    sf::Vector2f fimCauda; // onde a cauda é colada na moto
    sf::Color RGB; // cor na classe da biblioteca
public: // métodos públicos
    Moto();
    ~Moto();

    sf::Vector2f getFimCauda() const;
    sf::Sprite getForma() const;
    sf::Color getRGB() const;

    void mover();
    void mudarCima();
    void mudarBaixo();
    void mudarEsquerda();
    void mudarDireita();

    void setPosicaoInicial(int,sf::Vector2f);
    void setCor(std::string);

    // atributo privado
    int posicao;
};

// Implementação dos métodos da moto

// Construtor
Moto::Moto(){
    
    posicao=-1;
};

// Destrutor
Moto::~Moto(){};

// mudarCima
// Virar a moto para cima
void Moto::mudarCima(){
    sf::Sprite novaSprite; // para configurar a nova textura
    if(posicao != 3 && posicao != 1 ){
        textura.loadFromFile(cor+"/cima.png");
        novaSprite.setTexture(textura);

        if(posicao == 0){ // se está virada pra direita
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x - (forma.getTexture()->getSize().x)/2    ,forma.getPosition().y - novaSprite.getTexture()->getSize().y + forma.getTexture()->getSize().x/2  ));
        }
        if(posicao == 2){ // se está virada pra esquerda
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x + forma.getTexture()->getSize().y - novaSprite.getTexture()->getSize().x/2 , forma.getPosition().y + forma.getTexture()->getSize().x/2 - novaSprite.getTexture()->getSize().y ) );
        }

        fimCauda.x = (novaSprite.getTexture()->getSize().x)/2;
        fimCauda.y = novaSprite.getTexture()->getSize().y;

        forma = novaSprite; // armazena a nova textura
        posicao = 1; // guarda posição p/ cima
    }
};
// fim mudarCima

// mudarBaixo
// Virar a moto para baixo
void Moto::mudarBaixo(){
    sf::Sprite novaSprite; // para configurar a nova textura

    if(posicao != 3 && posicao != 1 ){
        
    textura.loadFromFile(cor+"/baixo.png");
    novaSprite.setTexture(textura);
        if(posicao == 0){ // se está virada pra direita
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x - (novaSprite.getTexture()->getSize().x)/2  ,forma.getPosition().y + (forma.getTexture()->getSize().x)/2));
        }
        if(posicao == 2){ // se está virada pra esquerda
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x + forma.getTexture()->getSize().y - (novaSprite.getTexture()->getSize().x)/2  , forma.getPosition().y + (forma.getTexture()->getSize().x)/2 ));
        }
        
        fimCauda.x = (novaSprite.getTexture()->getSize().x)/2;
        fimCauda.y = 0;

        forma = novaSprite; // armazena a nova textura
        posicao = 3; // guarda a posição p/ baixo
    }
};
// fim mudarBaixo

// mudarDireita
// Virar a moto para a direita
void Moto::mudarDireita(){
    sf::Sprite novaSprite; // para configurar a nova textura

    
    if(posicao != 2 && posicao != 0 ){
        textura.loadFromFile(cor+"/direita.png");
    novaSprite.setTexture(textura);
        if(posicao == 3){ // se está virada para baixo
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().y)/2 ,forma.getPosition().y - (novaSprite.getTexture()->getSize().y)/2 ));
        }
        if(posicao == 1){ // se está virada para cima
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x + (forma.getTexture()->getSize().y)/2  , forma.getPosition().y + forma.getTexture()->getSize().x - (novaSprite.getTexture()->getSize().y)/2) );
        }

        fimCauda.x = 0;
        fimCauda.y = (novaSprite.getTexture()->getSize().y)/2;

        forma = novaSprite; // armazena a nova textura
        posicao = 0; // guarda a posição p/ a direita
    }
};
// fim mudarDireita

// mudarEsquerda
// Virar a moto para a esquerda
void Moto::mudarEsquerda(){
    sf::Sprite novaSprite; // para configurar a nova textura

  
    if(posicao != 2 && posicao != 0 ){
         textura.loadFromFile(cor+"/esquerda.png");
    novaSprite.setTexture(textura);
        if(posicao == 3){ // se está virada para baixo
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x - novaSprite.getTexture()->getSize().x + (forma.getTexture()->getSize().y)/2   , forma.getPosition().y - (novaSprite.getTexture()->getSize().y)/2 ));
        }
        if(posicao == 1){ // se está virada para cima
            novaSprite.setPosition(sf::Vector2f(forma.getPosition().x  + (forma.getTexture()->getSize().y)/2 - novaSprite.getTexture()->getSize().x   ,forma.getPosition().y - (novaSprite.getTexture()->getSize().y)/2 + forma.getTexture()->getSize().x  ));
        }

        fimCauda.x = novaSprite.getTexture()->getSize().x;
        fimCauda.y = (novaSprite.getTexture()->getSize().y)/2;

        forma = novaSprite; // armazena a nova textura
        posicao = 2; // guarda a posição p/ a esquerda
    }
};
// fim mudarEsquerda

// mover
// Move a moto utilizando a forma como classe da biblioteca gráfica
// Move-se de acordo com a posição
void Moto::mover(){
    if(posicao == 0)
        forma.move(0.8f,0.0f);
    if(posicao == 1)
        forma.move(0.0f,-0.8f); 
    if(posicao == 2)
        forma.move(-0.8f,0.0f);
    if(posicao == 3){
        forma.move(0.0f,0.8f);
    }
};
// fim mover

// getFimCauda
// retorna o fim da cauda (onde ela é grudada na moto)
sf::Vector2f Moto::getFimCauda() const{
    return fimCauda;
};
// fim getFimCauda

// getForma
// Retorna a forma da moto
sf::Sprite Moto::getForma() const{
    return forma;
};
// fim getForma

// setPosicaoInicial
// Determina a posicao inicial da moto
void Moto::setPosicaoInicial(int x, sf::Vector2f vetor){
    posicao=x;
    forma.setPosition(vetor);
}
// fim setPosicaoInicial

// setCor
// Determina o nome da cor
void Moto::setCor(std::string c){
    cor=c;
    if(cor == "Azul")
        RGB = sf::Color(0,255,255);
    if(cor == "Laranja")
        RGB = sf::Color(255,60,0);
};
// fim setCor
