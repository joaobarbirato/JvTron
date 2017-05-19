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
#include <fstream>
#include "Tela.hpp"
#include "Moto.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Mapeamento das teclas pressionadas
enum InputType{
    KeyboardInput
};
 
struct MyKeys{
    InputType myInputType;
    sf::Event::EventType myEventType;
    sf::Keyboard::Key myKeyCode;
};

bool TestEvent(MyKeys k, sf::Event e){
    // Evento do teclado
    if (k.myInputType == KeyboardInput &&
        k.myEventType == e.type &&
        k.myKeyCode == e.key.code){
        return (true);
    }
    return (false);
};

// Estrutura do Campo
class Campo : public Tela{
private:
    // atributos privados
    Moto tron; // I fight for the users! (moto azul)
    Moto rinz; // Defend the perfect system! (moto laranja)
    Fila<sf::Vertex> FETron; // Fila de Exibição da cauda da moto azul
    Fila<sf::Vertex> FERinz; // Fila de Exibição da cauda da moto laranja
    Fila<sf::RectangleShape> paredesTron, paredesRinz; // Filas de armazenamento das paredes da moto azul
    Fila<sf::RectangleShape> auxMudaOriTC; // Filas de armazenamento das paredes da moto laranja
    sf::Vector2f auxMudaOriT, auxMudaOriR; // Auxiliares no armazenamento da posiçao quando há mudança de orientação

    sf::Vertex tempCauda; // cauda temporária para inserir nas filas de exibição
    sf::RectangleShape tempRetangulo; // retangulo temporario para verificação de elementos nas filas de armazenamento

    bool virouTron = false; // indica se a moto azul virou
    bool virouRinz = false; // indica se a moto laranja virou
    bool ok; // variavel para os métodos da fila
    int iT=0, iR=0; // iteradores da moto azul e laranja, para auxílio do armazenamento das paredes na fila
    int j=0; // contador/iterador para o loop de vericação de colisão

    sf::Vector2f inicioTron, inicioRinz; // posição de inicio de cada Insere nas fila de armazenamentos das paredes

    // métodos privados
    void InsereParede(Fila<sf::RectangleShape>&, sf::Vector2f&, sf::Vector2f&);
    float meuAbs(const float&);
    void desenha(sf::RenderWindow &) const;
public: // métodos públicos
    Campo();
    ~Campo();
    virtual int Run(sf::RenderWindow &App);
};

// Implementação dos métodos do Campo

// Construtor
// Configura alguns atributos da classe
Campo::Campo(){
    tron.setCor("Azul");
    rinz.setCor("Laranja");

    FETron.Reset();
    FERinz.Reset();

    tron.mudarDireita();
    rinz.mudarEsquerda();

    this->tron.setPosicaoInicial(0,sf::Vector2f(70,80));
    this->rinz.setPosicaoInicial(2,sf::Vector2f(690, 500));

    auxMudaOriR= rinz.getForma().getPosition() + rinz.getFimCauda() + sf::Vector2f(-50.0f,0.0f);
    auxMudaOriT= tron.getForma().getPosition() + tron.getFimCauda() + sf::Vector2f(50.0f,0);

    inicioTron = tron.getForma().getPosition() + tron.getFimCauda();
    inicioRinz = rinz.getForma().getPosition() + rinz.getFimCauda();
};
// fim Construtor

// Destrutor
Campo::~Campo(){};

// Run
// Recebe por referência a janela da biblioteca gráfica
int Campo::Run(sf::RenderWindow &App){
    // declaração de variáveis
    sf::Event Event;
    sf::Sprite SauxMudaOriT;
    bool semChoqueT = false, semChoqueR = false; // recebe true se não há choque com as paredes
    bool Running = true; // controle do loop do jogo
    sf::RectangleShape linha1,linha2,linha3,linha4; // paredes invisíveis do campo
    
    //      cima
    linha1.setPosition(sf::Vector2f(50, 65));
    linha1.setSize(sf::Vector2f(App.getSize().x-100, 1.0f));

    //      esquerda
    linha2.setPosition(sf::Vector2f(50, 65));
    linha2.setSize(sf::Vector2f(1.0f, App.getSize().y - 130));

    //      baixo
    linha3.setPosition(sf::Vector2f(50 + App.getSize().x-100, 65));
    linha3.setSize(sf::Vector2f(1.0f , App.getSize().y - 130));

    //      direita
    linha4.setPosition(sf::Vector2f(50, 65 + App.getSize().y - 130));
    linha4.setSize(sf::Vector2f(App.getSize().x-100, 1.0f));
    
// inicialização do mapa de teclas
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
// fim inicialização do mapa de teclas

    while (Running){ // loop da tela
        while(App.pollEvent(Event)){ // loop de eventos
            switch(Event.type){
                case sf::Event::Closed: // fechar a janela
                    App.close();
                    return (-1);
                    break;
            }

// Na implementação, a cauda exibida e a parede que ela expressa são elementos diferentes.
// Quando os iteradores marcam 50, armazena-se uma parede na fila de paredes.

            // Mudança de orientação da moto azul
            if (TestEvent(Keys["tron-Direita"], Event)){
                iT = 50;
                auxMudaOriT = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarDireita();
                virouTron = true; 
            }
            if (TestEvent(Keys["tron-Esquerda"], Event)){
                iT = 50;
                auxMudaOriT = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarEsquerda(); 
                virouTron = true; 
            }
            if (TestEvent(Keys["tron-Cima"], Event)){
                iT = 50;
                auxMudaOriT = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarCima();
                virouTron = true; 
            }
            if (TestEvent(Keys["tron-Baixo"], Event)){
                iT = 50;
                auxMudaOriT = tron.getForma().getPosition() + tron.getFimCauda();
                tron.mudarBaixo();
                virouTron = true; 
            }

            // Mudança de orientação da moto laranja
            if (TestEvent(Keys["rinz-Direita"], Event)){
                iR = 50;
//                virouTron=true; 
                auxMudaOriR = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarDireita();
                virouRinz = true;
            }
            if (TestEvent(Keys["rinz-Esquerda"], Event)){
                iR = 50;
                auxMudaOriR = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarEsquerda();
                virouRinz = true;
            }
            if (TestEvent(Keys["rinz-Cima"], Event)){
                iR = 50;
//                virouTron=true;
                auxMudaOriR = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarCima();
                virouRinz = true;
            }
            if (TestEvent(Keys["rinz-Baixo"], Event)){
                iR = 50;    
                virouTron=true;
//                auxMudaOriR = sf::Vector2f(rinz.getForma().getPosition().x + rinz.getauxMudaOriTX(),rinz.getForma().getPosition().y + rinz.getauxMudaOriTY()); 
                auxMudaOriR = rinz.getForma().getPosition() + rinz.getFimCauda();
                rinz.mudarBaixo();
                virouRinz = true;
            }
        }
        
        // Mudou de orientação ou não, insere-se na fila de exibição
        //  Inserir na fila de exibição da moto azul
        tempCauda.position = tron.getForma().getPosition() + tron.getFimCauda();
        tempCauda.color = sf::Color(0,255,255);
        FETron.Insere(tempCauda,ok);

        //  Inserir na fila de exibição da moto laranja
        tempCauda.position = rinz.getForma().getPosition() + rinz.getFimCauda();
        tempCauda.color = sf::Color(255,60,0);
        FERinz.Insere(tempCauda,ok);

        // Quando os iteradoes vão a 50:
        if(iT == 50){ // para a moto azul:
            if(!virouTron)
                auxMudaOriT = tron.getForma().getPosition() + tron.getFimCauda();
        
            InsereParede(paredesTron, inicioTron,auxMudaOriT ); // chamada para inserir uma parede na fila de paredes
            iT = 0;
            inicioTron=auxMudaOriT;
            virouTron=false;
        }
         if(iR == 50){ // para a moto laranja:
            if(!virouRinz)
                auxMudaOriR = rinz.getForma().getPosition() + rinz.getFimCauda(); // chamada para inserir uma parede na fila de paredes

            InsereParede(paredesRinz, inicioRinz,auxMudaOriR );
            iR = 0;
            inicioRinz=auxMudaOriR;
            virouRinz=false;
         }
        
// Verificações de choques nas filas de paredes (onde e por qual moto)
        for(j = 0; j < paredesTron.getNElementos(); j++){ // para paredes na moto azul
                paredesTron.Retira(tempRetangulo, ok); 
                paredesTron.Insere(tempRetangulo, ok);
                if(tron.getForma().getGlobalBounds().intersects(tempRetangulo.getGlobalBounds()) && j < paredesTron.getNElementos() - 2){ // se a azul bate
                    return (3); // a laranja ganha (TELA 3: Ganhou em laranja)
                    break;
                }
                if(rinz.getForma().getGlobalBounds().intersects(tempRetangulo.getGlobalBounds())){ // se a laranja bate
                    return (2); // a azul ganha (TELA 2: Ganhou em azul)
                    break;
                } 
                semChoqueT = true;
        }
 

        for(j = 0; j < paredesRinz.getNElementos(); j++){ // para paredes na moto laranja
                paredesRinz.Retira(tempRetangulo, ok);
                paredesRinz.Insere(tempRetangulo, ok);
                if(tron.getForma().getGlobalBounds().intersects(tempRetangulo.getGlobalBounds()) ){ // se a azul bate
                    return (3); // a laranja ganha (TELA 3: Ganhou em laranja)
                    break;
                }
                if(rinz.getForma().getGlobalBounds().intersects(tempRetangulo.getGlobalBounds()) && j < paredesRinz.getNElementos() - 2 ){
                    return (2); // a laranja ganha (TELA 2: Ganhou em azul)
                    break;
                }
                semChoqueR = true;
        }
       
        // Verificações de choque nas paredes do campo
        if(     tron.getForma().getGlobalBounds().intersects(linha1.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(linha2.getGlobalBounds())
             || tron.getForma().getGlobalBounds().intersects(linha3.getGlobalBounds()) || tron.getForma().getGlobalBounds().intersects(linha4.getGlobalBounds()) ) // se a azul bate
            return (3); // a laranja ganha (TELA 3: Ganhou em laranja)
        if(     rinz.getForma().getGlobalBounds().intersects(linha1.getGlobalBounds()) || rinz.getForma().getGlobalBounds().intersects(linha2.getGlobalBounds())
             || rinz.getForma().getGlobalBounds().intersects(linha3.getGlobalBounds()) || rinz.getForma().getGlobalBounds().intersects(linha4.getGlobalBounds()) ) // se a laranja bate
            return (2); // a azul ganha (TELA 2: Ganhou em azul)
                
        // mover motos
        tron.mover();
        rinz.mover();
        
        // contar nos iteradores
        iT++;
        iR++;

        // dese
        desenha(App);
        App.draw(FERinz.getDesenhoRastro(),FERinz.getNElementos(),sf::Points);
        App.draw(FETron.getDesenhoRastro(),FETron.getNElementos(),sf::Points);
        App.draw(rinz.getForma());
        App.draw(tron.getForma());
        App.display();
        App.clear();  
    } // fim loop da tela

    // não há como chegar até aqui mas, se acontecer, termine o programa.
    return (-1);
}
// fim Run

// Desenha
// Método que desenha na tela alguns elementos
void Campo::desenha(sf::RenderWindow & App) const{
    const float tamanhoFonte = 30;
    sf::Text titulo;
    sf::Font fonte;
    sf::RectangleShape sombraTexto; // retangulo por tras dos títulos
    sf::RectangleShape retanguloTras, retanguloFrente; // retangulos principais
    sf::RectangleShape linha; // linha base para a grade
    
    linha.setPosition(sf::Vector2f(0, 0));
    linha.setFillColor(sf::Color(0,255,255));
    linha.setSize(sf::Vector2f(800.0f, 1.0f ));
    
    retanguloFrente.setPosition(sf::Vector2f(50,65));
    retanguloFrente.setFillColor(sf::Color::Black);
    retanguloFrente.setOutlineThickness(1);
    retanguloFrente.setOutlineColor(sf::Color(0,255,255));
    retanguloFrente.setSize(sf::Vector2f(App.getSize().x-100, App.getSize().y - 130 ));

    retanguloTras.setPosition(sf::Vector2f(40, 55));
    retanguloTras.setFillColor(sf::Color::Black);
    retanguloTras.setOutlineThickness(1);
    retanguloTras.setOutlineColor(sf::Color(0,255,255));
    retanguloTras.setSize(sf::Vector2f(App.getSize().x-80, App.getSize().y - 110 ));

    sombraTexto.setPosition((sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 8, 14)));
    sombraTexto.setFillColor(sf::Color::Black);
    sombraTexto.setSize(sf::Vector2f(140,30));
    sombraTexto.setOutlineThickness(1);
    sombraTexto.setOutlineColor(sf::Color(0,255,255));

    if(!fonte.loadFromFile("Tr2n.ttf")){} // fonte dos títulos

    // Exibe grade
    for(int i = 0; i < 21; i++){
        linha.setPosition(sf::Vector2f(0, 30*i));
        App.draw(linha);
    }
    linha.setSize(sf::Vector2f(1.0f, 600.0f ));
    for(int i = 0; i < 21; i++){
        linha.setPosition(sf::Vector2f(40*i, 0));
        App.draw(linha);
    }
    
    titulo.setFont(fonte);
    titulo.setString("JvTron");
    titulo.setCharacterSize(tamanhoFonte);
    titulo.setPosition(sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 3, 10));
    titulo.setFillColor(sf::Color(0,255,255));

    // desenha na janela
    App.draw(sombraTexto);
    App.draw(titulo);
    titulo.setPosition(sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 3, App.getSize().y - 50));
    sombraTexto.setPosition((sf::Vector2f(App.getSize().x/2 - tamanhoFonte*2 - 8, App.getSize().y - 46)));
    App.draw(sombraTexto);
    App.draw(titulo);
    App.draw(retanguloTras);
    App.draw(retanguloFrente);
};
// fim desenha

// InsereParede
// Inserção de paredes p/ verificacao de colisoes
void Campo::InsereParede(Fila<sf::RectangleShape>& F, sf::Vector2f& posInicial, sf::Vector2f& posFinal){
        bool ok; // auxiliar para métodos da fila
    
        sf::RectangleShape linha;
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
// fim InsereParede

// meuAbs
// Função auxiliar de módulo escalar para floats
float Campo::meuAbs(const float& a){
    if(a < 0)
        return (-a);
    return (a);
};
// fim meuAbs