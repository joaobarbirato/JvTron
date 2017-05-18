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
    Fila<sf::RectangleShape> caudaT,caudaR;
    Fila<sf::RectangleShape> auxC;
    sf::Vector2f aux,aux1;
    sf::Vertex auxCauda;
    bool virou =false;
    bool virou2 =false;
    bool ok;
    int iT=0, iR=0; // iterators
    int j=0;
    sf::RectangleShape s,s1;

    Disco d;
    sf::Vector2f inicioTron, inicioRinz;

    void DinamicaSprite(Fila<sf::RectangleShape>&, sf::Vector2f&, sf::Vector2f&);
    void imprimeShapes(sf::RenderWindow &);
    float meuAbs(const float&);
public:
    Campo(void);
    virtual int Run(sf::RenderWindow &App);
    void desenha(sf::RenderWindow &) const;
};

Campo::Campo(void){
    
    inicioTron = sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
    inicioRinz = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY());
             
       
};

int Campo::Run(sf::RenderWindow &App){
    sf::Event Event;
    sf::Sprite SAux;
    bool indo,indo2= false;
    bool Running = true;
    tron.setCor("Verde");
    rinz.setCor("Laranja");
    cauda.Reset();
    cauda2.Reset();
    tron.mudarDireita();
    rinz.mudarEsquerda();
    this->tron.setPosicaoInicial(0,sf::Vector2f(60,60));
    this->rinz.setPosicaoInicial(2,sf::Vector2f(680,490));
    aux1= sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX() - 50.0f,rinz.getForma().getPosition().y + rinz.getAuxY());
    aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX() + 50.0f,tron.getForma().getPosition().y + tron.getAuxY());
    inicioTron = sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
    inicioRinz = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY());
         
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
                iT = 50;
                 aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                tron.mudarDireita();
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Esquerda"], Event)){
                iT = 50;
                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                tron.mudarEsquerda(); 
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Cima"], Event)){
                iT = 50;
                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                tron.mudarCima();
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Baixo"], Event)){
                iT = 50;
                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                tron.mudarBaixo();
                 virou=true; 
            }

            // teclas rinzzler
            if (TestEvent(Keys["rinz-Direita"], Event)){
                iR = 50;
                virou=true; 
                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                rinz.mudarDireita();
            }
            if (TestEvent(Keys["rinz-Esquerda"], Event)){
                iR = 50;
                virou=true;
                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                rinz.mudarEsquerda(); 
            }
            if (TestEvent(Keys["rinz-Cima"], Event)){
                iR = 50;
                virou=true;
                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                rinz.mudarCima();
            }
            if (TestEvent(Keys["rinz-Baixo"], Event)){
                iR = 50;    
                virou=true;
                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                rinz.mudarBaixo();
            }
        }
        
        
     
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

        if(iT==50){
            if(!virou)
                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
            DinamicaSprite(caudaT, inicioTron,aux );
            iT=0;
            inicioTron=aux;
            virou=false;
        }
         if(iR==50){
            if(!virou2)
                aux1= sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY());
            
            DinamicaSprite(caudaR, inicioRinz,aux1 );
            iR=0;
            inicioRinz=aux1;
         }
                     
        
        
        //desenha na tela o ratro e a tron
        desenha(App);
//         ver funcionamento da cauda - a parte da info
        
        for(j=0;j < caudaT.getNElementos() - 2 ;j++  ){
                caudaT.Retira(s,ok);
                caudaT.Insere(s,ok);
                if(tron.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) ){
                    printf("Fudeu 1 \n");    
                    return 3;
                    break;
                }
                if(rinz.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) ){
                 printf("Fudeu 2 \n");
                 return 2;
                 break;
                } 
                indo = true;
        }
        if(caudaT.getNElementos() > 2 && indo == true){
                caudaT.Retira(s,ok);
                caudaT.Insere(s,ok);
                caudaT.Retira(s,ok);
                caudaT.Insere(s,ok);
        }
        for(j=0;j <=caudaR.getNElementos() ;j++  ){
                caudaR.Retira(s,ok);
                 caudaR.Insere(s,ok);
                if(tron.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) ){
                    printf("Fudeu 1 \n");    
                    return 3;
                    break;
                }
                if(rinz.getForma().getGlobalBounds().intersects(s.getGlobalBounds()) ){
                 printf("Fudeu 2 \n");
                 return 2;
                 break;
                }
                indo2=true;
        }
         if(caudaR.getNElementos() > 2 && indo == true){
                caudaR.Retira(s,ok);
                caudaR.Insere(s,ok);
                caudaR.Retira(s,ok);
                caudaR.Insere(s,ok);
        }    
            
//             if (j >=caudaT.getNElementos() || j >= caudaR.getNElementos() ){
//                 break;
                
            
            
                
        rinz.mover();
        tron.mover();
      
         iT=iT+1;
        iR=iR+1;
//        imprimeShapes(App);
//         App.draw(cauda2.getDesenhoRastro(),cauda2.getNElementos(),sf::Points);
//        d.aparece( float(rand() % (App.getSize().x-50) + 50), float(rand() % (App.getSize().y-50)-20) + 50 , App);
        App.draw(cauda.getDesenhoRastro(),cauda.getNElementos(),sf::Points);
        App.draw(rinz.getForma());
        App.draw(tron.getForma());
//         App.draw(s);
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

void Campo::DinamicaSprite(Fila<sf::RectangleShape>& F, sf::Vector2f& posInicial, sf::Vector2f& posFinal){
    // Dinâmica de inserir sprites p/ verificacao de colisoes
        bool ok;
    
        sf::RectangleShape linha;
        sf::Vertex f;
        linha.setPosition(posInicial);
        if(posFinal.y == posInicial.y){ // moveu na horizontal
            linha.setSize(sf::Vector2f(meuAbs(posFinal.x - posInicial.x), 1.0f));
        }else{
            if(posFinal.x == posInicial.x){ // moveu na vertical
                linha.setSize(sf::Vector2f(1.0f, meuAbs(posFinal.y - posInicial.y)));
            }else{
                printf("----------------\n");
                printf("%f     %f\n",posFinal.x,posFinal.y);
                printf("%f     %f\n",posInicial.x,posInicial.y);
                printf("----------------\n");
                std::cout<<"sucesso"<<std::endl;
            }
        }
        printf("----------------\n");
                printf("%f     %f\n",posFinal.x,posFinal.y);
                printf("%f     %f\n",posInicial.x,posInicial.y);
                printf("----------------\n");
                std::cout<<"poha"<<std::endl;
        F.Insere(linha,ok);
    
};

float Campo::meuAbs(const float& a){
    if(a < 0)
        return -a;
    return a;
}

void Campo::imprimeShapes(sf::RenderWindow & app){
    sf::RectangleShape auxrs;
    Fila<sf::RectangleShape> auxf;
    bool auxb;
    while(!caudaT.Vazia()){
        caudaT.Retira(auxrs, auxb);
        if(auxb){
            auxf.Insere(auxrs,auxb);
            app.draw(auxrs);
        }
    }
    while(!auxf.Vazia()){
        auxf.Retira(auxrs,auxb);
        if(auxb)
            caudaT.Insere(auxrs,auxb);
    }
};    
