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
    Fila<sf::RectangleShape> caudaT,caudaR;
    Fila<sf::RectangleShape> auxC;
    sf::Vector2f aux,aux1;
    sf::Vertex auxCauda;
    bool virou =false;
    bool virou2 =false;
    sf::RectangleShape retanguloBordas;
    bool ok;
    int iT=0, iR=0; // iterators
    int j=0;
    sf::RectangleShape s,s1;

    Fila<sf::RectangleShape> FRecT, FRecR;
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
    
    tron.setCor("Verde");
    rinz.setCor("Laranja");
    cauda.Reset();
    cauda2.Reset();
    tron.mudarDireita();
    rinz.mudarEsquerda();
    this->tron.setPosicaoInicial(0,sf::Vector2f(70,80));
    this->rinz.setPosicaoInicial(2,sf::Vector2f(690, 500));
    aux1= rinz.getForma().getPosition() + rinz.getFimCauda() + sf::Vector2f(-50.0f,0.0f);// sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX() - 50.0f,rinz.getForma().getPosition().y + rinz.getAuxY());
    aux= tron.getForma().getPosition() + tron.getFimCauda() + sf::Vector2f(50.0f,0); //::Vector2f(tron.getForma().getPosition().x + tron.getAuxX() + 50.0f,tron.getForma().getPosition().y + tron.getAuxY());
    inicioTron = tron.getForma().getPosition() + tron.getFimCauda();
    inicioRinz = rinz.getForma().getPosition() + rinz.getFimCauda();
    printf("%i %i",this->tron.getForma().getPosition().x,this->tron.getForma().getPosition().y);
       
};

int Campo::Run(sf::RenderWindow &App){
    sf::Event Event;
    sf::Sprite SAux;
    bool indo,indo2= false;
    bool Running = true;
    sf::RectangleShape linha1,linha2,linha3,linha4;


    retanguloBordas.setPosition(sf::Vector2f(50,65));
    retanguloBordas.setFillColor(sf::Color::Black);
    retanguloBordas.setOutlineThickness(1);
    retanguloBordas.setOutlineColor(sf::Color(0,255,255));
    retanguloBordas.setSize(sf::Vector2f(App.getSize().x-100, App.getSize().y - 130 ));
    
    
    linha1.setPosition(sf::Vector2f(50, 65));
    linha1.setSize(sf::Vector2f(App.getSize().x-100, 1.0f));
    linha2.setPosition(sf::Vector2f(50, 65));
    linha2.setSize(sf::Vector2f(1.0f, App.getSize().y - 130));
    linha3.setPosition(sf::Vector2f(50 + App.getSize().x-100, 65));
    linha3.setSize(sf::Vector2f(1.0f , App.getSize().y - 130));
    linha4.setPosition(sf::Vector2f(50, 65 + App.getSize().y - 130));
    linha4.setSize(sf::Vector2f(App.getSize().x-100, 1.0f));
    
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
//                 aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                aux = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarDireita();
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Esquerda"], Event)){
                iT = 50;
//                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                aux = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarEsquerda(); 
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Cima"], Event)){
                iT = 50;
//                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                aux = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarCima();
                 virou=true; 
            }
            if (TestEvent(Keys["tron-Baixo"], Event)){
                iT = 50;
//                aux= sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
                aux = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarBaixo();
                 virou=true; 
            }

            // teclas rinzzler
            if (TestEvent(Keys["rinz-Direita"], Event)){
                iR = 50;
                virou=true; 
//                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarDireita();
            }
            if (TestEvent(Keys["rinz-Esquerda"], Event)){
                iR = 50;
                virou=true;
//                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarEsquerda(); 
            }
            if (TestEvent(Keys["rinz-Cima"], Event)){
                iR = 50;
                virou=true;
//                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarCima();
            }
            if (TestEvent(Keys["rinz-Baixo"], Event)){
                iR = 50;    
                virou=true;
//                aux1 = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY()); 
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarBaixo();
            }
        }
        
        
     
        auxCauda.position=tron.getForma().getPosition() + tron.getFimCauda();
        auxCauda.color = sf::Color(0,255,255);
        cauda.Insere(auxCauda,ok);
        auxCauda.position=rinz.getForma().getPosition() + rinz.getFimCauda();
        auxCauda.color = sf::Color(255,60,0);
        cauda2.Insere(auxCauda,ok);

        if(iT==50){
            if(!virou)
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
            //aux = sf::Vector2f(tron.getForma().getPosition().x + tron.getAuxX(),tron.getForma().getPosition().y + tron.getAuxY());
            DinamicaSprite(caudaT, inicioTron,aux );
            iT=0;
            inicioTron=aux;
            virou=false;
        }
         if(iR==50){
            if(!virou2)
                aux1 = rinz.getForma().getPosition() + rinz.getFimCauda();
            //aux1= sf::Vector2f(rinz.getForma().getPosition().x + rinz.getAuxX(),rinz.getForma().getPosition().y + rinz.getAuxY());
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
        if(tron.getForma().getGlobalBounds().intersects(linha1.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(linha2.getGlobalBounds())
             || tron.getForma().getGlobalBounds().intersects(linha3.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(linha4.getGlobalBounds()) )
        
            return 3;
        if(rinz.getForma().getGlobalBounds().intersects(linha1.getGlobalBounds()) || rinz.getForma().getGlobalBounds().intersects(linha2.getGlobalBounds())
             || rinz.getForma().getGlobalBounds().intersects(linha3.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(linha4.getGlobalBounds()) )
            return 2;
//             if (j >=caudaT.getNElementos() || j >= caudaR.getNElementos() ){
//                 break;
                
            
            
                
        rinz.mover();
        tron.mover();
      
         iT=iT+1;
        iR=iR+1;
//        imprimeShapes(App);
//         App.draw(cauda2.getDesenhoRastro(),cauda2.getNElementos(),sf::Points);
//        d.aparece( float(rand() % (App.getSize().x-50) + 50), float(rand() % (App.getSize().y-50)-20) + 50 , App);
        App.draw(cauda2.getDesenhoRastro(),cauda2.getNElementos(),sf::Points);
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
    const float tamanhoFonte = 30;
    int i;

    sf::Text titulo;
    sf::Font fonte;
    sf::RectangleShape sombraTexto;
    sf::RectangleShape retanguloTrasExibicao;
    sf::RectangleShape linha;
    
    linha.setPosition(sf::Vector2f(0, 0));
    linha.setFillColor(sf::Color(0,255,255));
    linha.setSize(sf::Vector2f(800.0f, 1.0f ));
        
    retanguloTrasExibicao.setPosition(sf::Vector2f(40, 55));
    retanguloTrasExibicao.setFillColor(sf::Color::Black);
    retanguloTrasExibicao.setOutlineThickness(1);
    retanguloTrasExibicao.setOutlineColor(sf::Color(0,255,255));
    retanguloTrasExibicao.setSize(sf::Vector2f(App.getSize().x-80, App.getSize().y - 110 ));

    if(!fonte.loadFromFile("Tr2n.ttf")){}

    for(i=0;i<21; i++){
        linha.setPosition(sf::Vector2f(0, 30*i));
        App.draw(linha);
    }
    
    linha.setSize(sf::Vector2f(1.0f, 600.0f ));
    for(i=0;i<21; i++){
        linha.setPosition(sf::Vector2f(40*i, 0));
        App.draw(linha);
    }
    sombraTexto.setPosition((sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 8, 14)));
    sombraTexto.setFillColor(sf::Color::Black);
    sombraTexto.setSize(sf::Vector2f(140,30));
    sombraTexto.setOutlineThickness(1);
    sombraTexto.setOutlineColor(sf::Color(0,255,255));
    
    titulo.setFont(fonte);
    titulo.setString("JvTron");
    titulo.setCharacterSize(tamanhoFonte);
    titulo.setPosition(sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 3, 10));
    titulo.setFillColor(sf::Color(0,255,255));

    //desenha na tela o ratro e a tron
    App.draw(sombraTexto);
    App.draw(titulo);
    titulo.setPosition(sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 3, App.getSize().y - 50));
    sombraTexto.setPosition((sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 8, App.getSize().y - 46)));
    App.draw(sombraTexto);
    App.draw(titulo);
    App.draw(retanguloTrasExibicao);
    App.draw(retanguloBordas);
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
            }
        }
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
