#include <iostream>
#include <fstream>
#include "Tela.hpp"
#include "Moto.hpp"
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
    sf::RectangleShape retanguloBordas;
    bool ok;
    int iT=0, iR; // iterators
    int j=0;
    sf::RectangleShape s,s1;

    Fila<sf::RectangleShape> FRecT, FRecR;
    sf::Vector2f inicioTron, inicioRinz;

    void DinamicaSprite(Fila<sf::RectangleShape>&,int&, sf::Vector2f&, Moto&);
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

    retanguloBordas.setPosition(sf::Vector2f(50, 50));
    retanguloBordas.setFillColor(sf::Color::Black);
    retanguloBordas.setOutlineThickness(1);
    retanguloBordas.setOutlineColor(sf::Color(0,255,255));
    retanguloBordas.setSize(sf::Vector2f(App.getSize().x-100, App.getSize().y*4/5 -100));
    
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
                    return (-1);
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
                iT = 500;
                tron.mudarDireita();
            }
            if (TestEvent(Keys["tron-Esquerda"], Event)){
                iT = 500;
                tron.mudarEsquerda(); 
            }
            if (TestEvent(Keys["tron-Cima"], Event)){
                iT = 500;
                tron.mudarCima();
            }
            if (TestEvent(Keys["tron-Baixo"], Event)){
                iT = 500;
                tron.mudarBaixo();
            }

            // teclas rinzzler
            if (TestEvent(Keys["rinz-Direita"], Event)){
                iR = 500;
                rinz.mudarDireita();
            }
            if (TestEvent(Keys["rinz-Esquerda"], Event)){
                iR = 500;
                rinz.mudarEsquerda(); 
            }
            if (TestEvent(Keys["rinz-Cima"], Event)){
                iR = 500;
                rinz.mudarCima();
            }
            if (TestEvent(Keys["rinz-Baixo"], Event)){
                iR = 500;
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
            
        if(!iT)
            inicioTron = tron.getForma().getPosition();
        if(!iR)
            inicioRinz = rinz.getForma().getPosition();

        DinamicaSprite(FRecT, iT, inicioTron, tron);
        DinamicaSprite(FRecR, iR, inicioRinz, rinz);
        
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
        App.draw(cauda.getDesenhoRastro(),cauda.getNElementos(),sf::Points);
        App.draw(rinz.getForma());
        App.draw(tron.getForma());
        App.display();
        //limpa a tela 
        App.clear();
        iT++;
        iR++;
    }
    //Never reaching this point normally, but just in case, exit the application
    return -1;
}

void Campo::desenha(sf::RenderWindow & App) const{
    const float tamanhoFonte = 20;

    sf::Text titulo;
    sf::Font fonte;
    sf::RectangleShape retanguloTrasExibicao;
    retanguloTrasExibicao.setPosition(sf::Vector2f(40, 40));
    retanguloTrasExibicao.setFillColor(sf::Color::Black);
    retanguloTrasExibicao.setOutlineThickness(1);
    retanguloTrasExibicao.setOutlineColor(sf::Color(0,255,255));
    retanguloTrasExibicao.setSize(sf::Vector2f(App.getSize().x-80, App.getSize().y*4/5 -80));

    if(!fonte.loadFromFile("Tr2n.ttf")){}

    titulo.setFont(fonte);
    titulo.setString("JvTron");
    titulo.setCharacterSize(tamanhoFonte);
    titulo.setPosition(sf::Vector2f(App.getSize().x/2 - tamanhoFonte*3, 10));
    titulo.setFillColor(sf::Color(0,255,255));

    //desenha na tela o ratro e a tron
    App.draw(titulo);
    App.draw(retanguloTrasExibicao);
    App.draw(retanguloBordas);
    return;
}

void Campo::DinamicaSprite(Fila<sf::RectangleShape>& F,int& i, sf::Vector2f& posInicial, Moto& m){
    // Dinâmica de inserir sprites p/ verificacao de colisoes
    if(i==500){
        sf::RectangleShape linha;
        linha.setPosition(posInicial);
        linha.setFillColor(sf::Color(0,255,255));
        if(m.getForma().getPosition().y == posInicial.y) // moveu na horizontal
            linha.setSize(sf::Vector2f(float(abs(m.getForma().getPosition().y - posInicial.y)),1.0f));
        if(m.getForma().getPosition().x == posInicial.x) // moveu na vertical
            linha.setSize(sf::Vector2f(1.0f, float(abs(m.getForma().getPosition().x - posInicial.x))));
        i = 0;
    }
};