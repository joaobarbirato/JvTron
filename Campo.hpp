#include <iostream>
#include <fstream>
#include "Tela.hpp"
#include "Disco.hpp"
#include "Moto.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum InputType
{
    KeyboardInput
};
 
struct MyKeys
{
    InputType myInputType;
    sf::Event::EventType myEventType;
    sf::Keyboard::Key myKeyCode;
};
bool TestEvent(MyKeys k, sf::Event e)
{
    // Keyboard event
    if (k.myInputType == KeyboardInput &&
        k.myEventType == e.type &&
        k.myKeyCode == e.key.code)
    {
        return (true);
    }
    return (false);
};
class Campo : public Tela{
private:
    Moto moto;
    Moto moto2;
    Fila cauda;
    Fila cauda2;
    Fila aux,aux1;
    sf::Vertex auxCauda;
    bool ok;
    int j=0;
    sf::RectangleShape s,s1;
    Disco d;
public:
	Campo(void);
	virtual int Run(sf::RenderWindow &App);
	void desenha(sf::RenderWindow &) const;
};

Campo::Campo(void){};

int Campo::Run(sf::RenderWindow &App){
	sf::Event Event;
	bool Running = true;
    
    moto.setCor("Verde");
    moto2.setCor("Laranja");
    moto.mudarDireita();
    moto2.mudarEsquerda();
    this->moto.setPosicaoInicial(0,sf::Vector2f(60,60));
    this->moto2.setPosicaoInicial(2,sf::Vector2f(680,490));
    printf("%i %i",this->moto.getForma().getPosition().x,this->moto.getForma().getPosition().y);
    
    std::map<std::string,MyKeys> Keys;
    MyKeys key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::D;
    Keys["Moto1-Direita"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::A;
    Keys["Moto1-Esquerda"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::S;
    Keys["Moto1-Baixo"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::W;
    Keys["Moto1-Cima"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::K;
    Keys["Moto2-Baixo"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::L;
    Keys["Moto2-Direita"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::J;
    Keys["Moto2-Esquerda"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::I;
    Keys["Moto2-Cima"] = key;  
    
    
    
	while (Running){ // gameloop
		while(App.pollEvent(Event)){ // eventloop
            // pensar em eventos pra Ganhou e Perdeu
            switch(Event.type){
                //evento para fechar
                case sf::Event::Closed:
                    App.close();
                    break;
                //evento quando aumentar/diminuir, necessario ?    
                case sf::Event::Resized:
                    printf("Nova janela com width: %i e com height: %i \n",Event.size.width,Event.size.height);
                    break;
                //"aparece" o q a pessoa escreve
                case sf::Event::TextEntered:
                    if(Event.text.unicode < 128)
                        printf("%c",Event.text.unicode);         
                    break;
               
            }
            if (TestEvent(Keys["Moto1-Direita"], Event))
            {
                moto.mudarDireita();
                
            }
            if (TestEvent(Keys["Moto1-Esquerda"], Event))
            {
               moto.mudarEsquerda(); 
            }
            if (TestEvent(Keys["Moto1-Cima"], Event))
            {
                moto.mudarCima();
            }
            if (TestEvent(Keys["Moto1-Baixo"], Event))
            {
                moto.mudarBaixo();
            }
            if (TestEvent(Keys["Moto2-Direita"], Event))
            {
                moto2.mudarDireita();
                
            }
            if (TestEvent(Keys["Moto2-Esquerda"], Event))
            {
               moto2.mudarEsquerda(); 
            }
            if (TestEvent(Keys["Moto2-Cima"], Event))
            {
                moto2.mudarCima();
            }
            if (TestEvent(Keys["Moto2-Baixo"], Event))
            {
                moto2.mudarBaixo();
            }
        }
        
            moto2.mover();
            moto.mover();
         
            auxCauda.position=moto.getForma().getPosition();
            auxCauda.position.y+=moto.getAuxY();
            auxCauda.position.x+=moto.getAuxX();;
            auxCauda.color = sf::Color(0,255,255);
            cauda.Insere(auxCauda,ok);
            auxCauda.position=moto2.getForma().getPosition();
            auxCauda.position.y+=moto2.getAuxY();
            auxCauda.position.x+=moto2.getAuxX();;
            auxCauda.color = sf::Color(255,60,0);
            cauda2.Insere(auxCauda,ok);
            
        
        
        //desenha na tela o ratro e a moto
        desenha(App);
//         ver funcionamento da cauda - a parte da info
        aux=cauda;
        aux1=cauda2;
        
        s.setSize(sf::Vector2f(1,1));
        s1.setSize(sf::Vector2f(1,1));
        for(j=0;j<cauda.getNElementos() - 100;j++){
            aux.Retira(auxCauda,ok);
            s.setPosition(auxCauda.position);
            aux1.Retira(auxCauda,ok);
            s1.setPosition(auxCauda.position);
            if(moto.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) || moto.getForma().getGlobalBounds().intersects(s1.getGlobalBounds())  ){
                 printf("Fudeu 1 \n");    
                 return 3;
                  break;
                  
            }
            printf("%i\n",j);
            if(moto2.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) || moto2.getForma().getGlobalBounds().intersects(s1.getGlobalBounds()) ){
                 printf("Fudeu 2 \n");
                 return 2;
                 break;
            }   
        }
        
      
        
        App.draw(cauda2.getDesenhoRastro(),20000,sf::Points);
//        d.aparece( float(rand() % (App.getSize().x-50) + 50), float(rand() % (App.getSize().y-50)-20) + 50 , App);
        App.draw(cauda.getDesenhoRastro(),20000,sf::Points);
        App.draw(moto2.getForma());
        App.draw(moto.getForma());
        App.display();
        //limpa a tela 
        App.clear();
	}
	//Never reaching this point normally, but just in case, exit the application
	return -1;
}

void Campo::desenha(sf::RenderWindow & App) const{
    const float tamanhoFonte = 20;
    float largura = App.getSize().x;
    float altura = App.getSize().y;
    sf::Text titulo;
    sf::Font fonte;
    
    if(!fonte.loadFromFile("Tr2n.ttf")){}

    titulo.setFont(fonte);
    titulo.setString("JvTron");
    titulo.setCharacterSize(tamanhoFonte);
    titulo.setPosition(sf::Vector2f(largura/2 - tamanhoFonte*3, 10));
    titulo.setFillColor(sf::Color(0,255,255));

    // barras de campo da esquerda
    sf::Vertex vertEsq1[] =  {
        sf::Vertex(sf::Vector2f(50, 50), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(50, altura*4/5 - 50), sf::Color(0,255,255))
    };
    sf::Vertex vertEsq2[] =  {
        sf::Vertex(sf::Vector2f(40, 40), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(40, altura*4/5 - 40), sf::Color(0,255,255))
    };

    // barras de campo da direita
    sf::Vertex vertDir1[] =  {
        sf::Vertex(sf::Vector2f(largura - 50, 50), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 50, altura*4/5 - 50), sf::Color(0,255,255))
    };
    sf::Vertex vertDir2[] =  {
        sf::Vertex(sf::Vector2f(largura - 40, 40), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 40, altura*4/5 - 40), sf::Color(0,255,255))
    };

    // barras de campo de cima
    sf::Vertex horCima1[] =  {
        sf::Vertex(sf::Vector2f(50, 50), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 50, 50), sf::Color(0,255,255))
    };
    sf::Vertex horCima2[] =  {
        sf::Vertex(sf::Vector2f(40, 40), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 40, 40), sf::Color(0,255,255))
    };

    // barras de campo de baixo
    sf::Vertex horBaixo1[] = {
        sf::Vertex(sf::Vector2f(50, altura*4/5 - 50), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 50, altura*4/5 - 50), sf::Color(0,255,255))
    };
    sf::Vertex horBaixo2[] = {
        sf::Vertex(sf::Vector2f(40, altura*4/5- 40), sf::Color(0,255,255)),
        sf::Vertex(sf::Vector2f(largura - 40, altura*4/5 - 40), sf::Color(0,255,255))
    };

    //desenha na tela o ratro e a moto
    App.draw(titulo);
    App.draw(vertEsq1, 2, sf::Lines);
    App.draw(vertEsq2, 2, sf::Lines);
    App.draw(vertDir1, 2, sf::Lines);
    App.draw(vertDir2, 2, sf::Lines);
    App.draw(horCima1, 2, sf::Lines);
    App.draw(horCima2, 2, sf::Lines);
    App.draw(horBaixo1, 2, sf::Lines);
    App.draw(horBaixo2, 2, sf::Lines);
    return;
}

