#include <iostream>
#include <fstream>
#include "Tela.hpp"
#include "Moto.hpp"
#include "Disco.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum InputType{
    KeyboardInput
};
 
struct MyKeys{
    InputType myInputType;
    sf::Event::EventType myEventType;
    sf::Keyboard::Key myKeyCode;
};

bool TestEvent(MyKeys k, sf::Event e){
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
    Moto tron; //(sf::Color(0,255,255));
    Moto rinz; //(sf::Color(255,60,0));
    Fila<sf::Vertex> cauda;
    Fila<sf::Vertex> cauda2;
    Fila<sf::Vertex> aux,aux1;
    sf::Vertex auxCauda;
    bool ok;
    int i=0;
    int j=0;
    sf::RectangleShape s,s1;

    Disco d;
    Fila<sf::Sprite> FSpriteT, FSpriteR;
    sf::Vector2f inicioTron, inicioRinz;

    void DinamicaSprite(Fila<sf::Sprite>&,int&, sf::Vector2f&, Moto&);
public:
    Campo(void);
    virtual int Run(sf::RenderWindow &App);
    void desenha(sf::RenderWindow &) const;
};

Campo::Campo(void){};

int Campo::Run(sf::RenderWindow &App){
    sf::Event Event;
    sf::Sprite SAux;
    bool Running = true;
    tron.setCor("Verde");
    rinz.setCor("Laranja");
    
    tron.mudarDireita();
    rinz.mudarEsquerda();
    this->tron.setPosicaoInicial(0,sf::Vector2f(60,60));
    this->rinz.setPosicaoInicial(2,sf::Vector2f(680,490));
    printf("%i %i",this->tron.getForma().getPosition().x,this->tron.getForma().getPosition().y);
    
    std::map<std::string,MyKeys> Keys;
    MyKeys key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::D;
    Keys["tron-Direita"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::A;
    Keys["tron-Esquerda"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::S;
    Keys["tron-Baixo"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::W;
    Keys["tron-Cima"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::K;
    Keys["rinz-Baixo"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::L;
    Keys["rinz-Direita"] = key;

    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::J;
    Keys["rinz-Esquerda"] = key;
    
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::I;
    Keys["rinz-Cima"] = key;  
    

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
            // teclas tron
            if (TestEvent(Keys["tron-Direita"], Event)){
//                DinamicaSprite(FSpriteT, FSpriteR, i, inicioTron, inicioRinz);
                tron.mudarDireita();
            }
            if (TestEvent(Keys["tron-Esquerda"], Event)){
//                DinamicaSprite(FSpriteT, FSpriteR, i, inicioTron, inicioRinz);
                tron.mudarEsquerda(); 
            }
            if (TestEvent(Keys["tron-Cima"], Event)){
//                DinamicaSprite(FSpriteT, FSpriteR, i, inicioTron, inicioRinz);
                tron.mudarCima();
            }
            if (TestEvent(Keys["tron-Baixo"], Event)){
//                DinamicaSprite(FSpriteT, FSpriteR, i, inicioTron, inicioRinz);
                tron.mudarBaixo();
            }

            // teclas rinzzler
            if (TestEvent(Keys["rinz-Direita"], Event)){
                rinz.mudarDireita();
            }
            if (TestEvent(Keys["rinz-Esquerda"], Event)){
               rinz.mudarEsquerda(); 
            }
            if (TestEvent(Keys["rinz-Cima"], Event)){
                rinz.mudarCima();
            }
            if (TestEvent(Keys["rinz-Baixo"], Event)){
                rinz.mudarBaixo();
            }
        }
        
        rinz.mover();
        tron.mover();
     
        auxCauda.position=tron.getForma().getPosition();
        auxCauda.position.y+=tron.getAuxY();
        auxCauda.position.x+=tron.getAuxX();;
        auxCauda.color = sf::Color(0,255,255);
        cauda.Insere(auxCauda,ok);
        auxCauda.position=rinz.getForma().getPosition();
        auxCauda.position.y+=rinz.getAuxY();
        auxCauda.position.x+=rinz.getAuxX();;
        auxCauda.color = sf::Color(255,60,0);
        cauda2.Insere(auxCauda,ok);
            
        
        
        //desenha na tela o ratro e a tron
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
            if(tron.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(s1.getGlobalBounds())  ){
                 printf("Fudeu 1 \n");    
                 return 3;
                  break;
            }
//            printf("%i\n",j);
            if(rinz.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) || rinz.getForma().getGlobalBounds().intersects(s1.getGlobalBounds()) ){
                 printf("Fudeu 2 \n");
                 return 2;
                 break;
            }   
        }
        
      
        
        App.draw(cauda2.getDesenhoRastro(),cauda2.getNElementos(),sf::Points);
//        d.aparece( float(rand() % (App.getSize().x-50) + 50), float(rand() % (App.getSize().y-50)-20) + 50 , App);
        App.draw(cauda.getDesenhoRastro(),cauda.getNElementos(),sf::Points);
        App.draw(rinz.getForma());
        App.draw(tron.getForma());
        App.display();
        //limpa a tela 
        App.clear();
        i++;
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

    //desenha na tela o ratro e a tron
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

void Campo::DinamicaSprite(Fila<sf::Sprite>& F,int& i, sf::Vector2f& posInicial, Moto& m){
    // Dinâmica de inserir sprites p/ verificacao de colisoes
    sf::Sprite SAux;
    bool ok;
    if(!i){ // guardar a primeira posicao
        posInicial = m.getForma().getPosition();
    }else{
        if(i == 500){ // 50 ou se a tron vira
            SAux.setPosition(inicioTron -  m.getForma().getPosition());
            SAux.setColor(sf::Color(0,255,255));
            std::cout<<"inseriu tron"<<std::endl;
            F.Insere(SAux, ok);
        }
    }
};