#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
/*
g++ -c main.cpp && g++ main.o Tela.cpp Menu.cpp Campo.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

*/

static const float VIEW_HEIGHT = 1500;
//void resizeView(const sf::RenderWindow& window, sf::View& view);
void drawCampo(sf::RenderWindow &);

int main (){
    
    sf::RenderWindow window(sf::VideoMode(1000,1000),"SFML tutorial",sf::Style::Close | sf::Style::Resize);
//    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));
    std::string playing = "playing";
    Menu menu(window.getSize().x, window.getSize().y);
    sf::Sprite player[4]; // retangulo para a moto
    sf::Sprite moto;
    //textura para a moto
    sf::Texture playert;
    sf::Texture playert2;
    playert2.loadFromFile("direita.png");
    player[0].setTexture(playert2);
    playert.loadFromFile("cima.png");
    player[1].setTexture(playert);
    playert2.loadFromFile("esquerda.png");
    player[2].setTexture(playert2);
    playert.loadFromFile("baixo.png");
    player[3].setTexture(playert);

    sf::Vertex vertex[10000]; //esse vai ser o tipo da pilha q vai ser usado
    int i=0,j=0; // contadores para rodar o vetor e adicionar por onde ele passa
    int x=0,y=0; // valores para acertar o ratro confome a virada da moto

    sf::Event evnt;
    while(window.isOpen()){
        FILE * taJogando;
        taJogando = fopen("jogo.bin", "rb");
        if(taJogando != NULL){ // jogo
            while(window.pollEvent(evnt)){
                switch(evnt.type){
                
                    //evento para fechar
                    case sf::Event::Closed:
                        window.close();
                        break;

                    //evento quando aumentar/diminuir, necessario ?    
                    case sf::Event::Resized:
                        printf("Nova janela com width: %i e com height: %i \n",evnt.size.width,evnt.size.height);
                        break;
                    //"aparece" o q a pessoa escreve
                    case sf::Event::TextEntered:
                        if(evnt.text.unicode < 128)
                            printf("%c",evnt.text.unicode);         
                        break;
                    case sf::Event::KeyPressed:
                        switch(evnt.key.code){
                            case sf::Keyboard::End:
                                system("rm jogo.bin");
                                break;
                            
                            case sf::Keyboard::A:
                                
                                 if(j == 1){
                                    player[2].setPosition(sf::Vector2f(moto.getPosition().x  + (moto.getTexture()->getSize().x)/2 - player[2].getTexture()->getSize().x   ,moto.getPosition().y - (player[2].getTexture()->getSize().y)/2 + moto.getTexture()->getSize().y  ));
                                }if(j==3){
                                    player[2].setPosition(sf::Vector2f(moto.getPosition().x - player[2].getTexture()->getSize().x + (moto.getTexture()->getSize().x)/2   , moto.getPosition().y - (player[2].getTexture()->getSize().y)/2 ));
                                }
                                x=player[2].getTexture()->getSize().x;
                                y=(player[2].getTexture()->getSize().y)/2;
                                 moto=player[2];
                                
                                j=2;
                                break;
                            case sf::Keyboard::S:
                                if(j == 0){
                                    player[3].setPosition(sf::Vector2f(moto.getPosition().x - (player[3].getTexture()->getSize().x)/2  ,moto.getPosition().y + (moto.getTexture()->getSize().y)/2 ));
                                }
                                if(j == 2){
                                    player[3].setPosition(sf::Vector2f(moto.getPosition().x + moto.getTexture()->getSize().x - (player[3].getTexture()->getSize().x)/2  , moto.getPosition().y + (moto.getTexture()->getSize().y)/2 ));
                                }
                                x= (player[3].getTexture()->getSize().x)/2;
                                y=0;
                                moto=player[3];
                                j=3;
                                break;
                            case sf::Keyboard::D:
                                if(j == 3){
                                    player[0].setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2 ,moto.getPosition().y - (player[0].getTexture()->getSize().y)/2 ));
                                }
                                if(j == 1){
                                    player[0].setPosition(sf::Vector2f(moto.getPosition().x + (moto.getTexture()->getSize().x)/2  , moto.getPosition().y + moto.getTexture()->getSize().y - (player[0].getTexture()->getSize().y)/2) );
                                }
                                x=0;
                                y=(player[2].getTexture()->getSize().y)/2;
                                moto=player[0];
                                j=0;
                                break;
                            case sf::Keyboard::W:
                                if(j == 0){
                                    player[1].setPosition(sf::Vector2f(moto.getPosition().x - (player[1].getTexture()->getSize().x)/2 ,moto.getPosition().y  + (moto.getTexture()->getSize().y)/2  - player[1].getTexture()->getSize().y ));
                                }
                                if(j == 2){
                                    player[1].setPosition(sf::Vector2f(moto.getPosition().x + moto.getTexture()->getSize().x - (player[1].getTexture()->getSize().x)/2 , moto.getPosition().y +  (moto.getTexture()->getSize().y)/2 - player[1].getTexture()->getSize().y ));
                                }
                                y=player[1].getTexture()->getSize().y;
                                x=(player[1].getTexture()->getSize().x)/2;
                                moto=player[1];
                                j=1;
                                break;
                        }
                        break;
                }
            }
            
            if (evnt.type == sf::Event::KeyReleased ){
                //caso a pessoa aperte o A
                if (evnt.key.code == sf::Keyboard::A){
                    //a moto estava antes em qual rotação ?
                    moto.move(-1.0f,0.0f);
                }
                //caso a pessoa aperte o S
               if (evnt.key.code == sf::Keyboard::S){
                    //a moto estava antes em qual rotação ?
                    moto.move(0.0f,1.0f);    
                }
                //caso a pessoa aperte o D
                if (evnt.key.code == sf::Keyboard::D){
                    //a moto estava antes em qual rotação ?
                    moto.move(1.0f,0.0f);
                }   
                //caso a pessoa aperte o D
                if (evnt.key.code == sf::Keyboard::W){
                    //a moto estava antes em qual rotação ?
                    moto.move(0.0f,-1.0f);    
                }
            }
            //adiciona as posições que ela passa, menos a igual q a anterior
            if(i<10000 && vertex[i-1].position!=moto.getPosition() ){
               vertex[i].position=moto.getPosition();
               vertex[i].position.y+=y;
               vertex[i].position.x+=x;
               vertex[i].color = sf::Color(0,255,255);
               i++;
            }
            
            //desenha na tela o ratro e a moto
            window.draw(vertex,10000,sf::Points);
            window.draw(moto);
            window.display();
            //limpa a tela 
            window.clear();
            fclose(taJogando);
        }else{ // menu
            while(window.pollEvent(evnt)){
                switch(evnt.type){
                    case sf::Event::KeyPressed: // teste do menu
                        switch(evnt.key.code){
                            case sf::Keyboard::Up:
                                menu.MovaParaCima();
                                break;
                            case sf::Keyboard::Down:
                                menu.MovaParaBaixo();
                                break;
                            case sf::Keyboard::Return:
                                switch(menu.ItemApertado()){
                                    case 0:
                                        taJogando = fopen("jogo.bin", "wb");
                                        fwrite(&playing,1,sizeof(std::string),taJogando);
                                        fclose(taJogando);
                                        break;
                                    case 1:
                                        break;
                                    case 2:
                                        window.close();
                                        break;
                                }
                                break;
                        }
                        break;
                    //evento para fechar
                    case sf::Event::Closed:
                        window.close();
                        break;
    
                    //evento quando aumentar/diminuir, necessario ?    
                    case sf::Event::Resized:
                        //resizeView(window, view);
                        printf("Nova janela com width: %i e com height: %i \n",evnt.size.width,evnt.size.height);
                        break;
                    //"aparece" o q a pessoa escreve
                    case sf::Event::TextEntered:
                        if(evnt.text.unicode < 128)
                            printf("%c",evnt.text.unicode);            
                        break;
                }        
            }
            window.clear();
 //         view.setCenter(menu.getCentro());
 //           window.setView(view);
            menu.desenha(window);
            //limpa a tela 
            window.display();

        }
    }
    return 0;
}
/*
void resizeView(const sf::RenderWindow& window, sf::View& view){
    float aspectRatio = float(window.getSize().x/window.getSize().y);
    view.setSize(VIEW_HEIGHT*aspectRatio, VIEW_HEIGHT);
};
*/
void drawCampo(sf::RenderWindow & window){
    const float tamanhoFonte = 20;

    float largura = window.getSize().x;
    float altura = window.getSize().y;
    sf::Text titulo;
    sf::Font fonte;

    fonte.loadFromFile("TRON.TTF");

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
    window.draw(titulo);
    window.draw(vertEsq1, 2, sf::Lines);
    window.draw(vertEsq2, 2, sf::Lines);
    window.draw(vertDir1, 2, sf::Lines);
    window.draw(vertDir2, 2, sf::Lines);
    window.draw(horCima1, 2, sf::Lines);
    window.draw(horCima2, 2, sf::Lines);
    window.draw(horBaixo1, 2, sf::Lines);
    window.draw(horBaixo2, 2, sf::Lines);
    return;
}