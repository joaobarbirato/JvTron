#include <iostream>
#include "Tela.hpp"
#include "Moto.h"
#include <SFML/Graphics.hpp>

class Campo : public Tela{
private:
    Moto moto;
    sf::Vertex c;
    sf::Vertex primeiro;
    sf::Vertex teste [100];
    Fila cauda;
    sf::Vertex auxCauda;
    bool ok;
    int i=0;
    bool deuCerto,deuCerto1;// contadores para rodar o vetor e adicionar por onde ele passa
public:
	Campo(void);
	virtual int Run(sf::RenderWindow &App);
	void desenha(sf::RenderWindow &) const;
};

Campo::Campo(void){
    moto.mudarDireita();

}

int Campo::Run(sf::RenderWindow &App){
	sf::Event Event;
	bool Running = true;

	while (Running){ // gameloop
		while(App.pollEvent(Event)){ //
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
                case sf::Event::KeyPressed:
                    switch(Event.key.code){
                        case sf::Keyboard::End:
                            return 0;
                            break;
                        
                        case sf::Keyboard::A:
                            moto.mudarEsquerda();
                            break;
                        case sf::Keyboard::S:
                            moto.mudarBaixo();
                            break;
                        case sf::Keyboard::D:
                            moto.mudarDireita();
                            break;
                        case sf::Keyboard::W:
                            moto.mudarCima();
                            break;
                    }
                    break;
            }
        }
        if (Event.type == sf::Event::KeyReleased ){
            //caso a pessoa aperte o A
            if (Event.key.code == sf::Keyboard::A){
                moto.moverEsquerda();
            }
            //caso a pessoa aperte o S
            if (Event.key.code == sf::Keyboard::S){
                moto.moverBaixo();
            }
            //caso a pessoa aperte o D
            if (Event.key.code == sf::Keyboard::D){
                moto.moverDireita();
            }   
            //caso a pessoa aperte o D
            if (Event.key.code == sf::Keyboard::W){
                moto.moverCima();
            }
        
            auxCauda.position=moto.getForma().getPosition();
             auxCauda.position.y+=moto.getAuxY();
             auxCauda.position.x+=moto.getAuxX();;
            auxCauda.color = sf::Color(0,255,255);
            cauda.Insere(auxCauda,ok);
            i++;
            
                    printf("%i\n",i);
        }
    
        
        //desenha na tela o ratro e a moto
        desenha(App);
//         ver funcionamento da cauda - a parte da info
        
        cauda.Retira(c,deuCerto);
        primeiro=c;
        cauda.Insere(c,deuCerto1);
        do{
            App.draw(&c,1,sf::Points);
            cauda.Retira(c,deuCerto);
            cauda.Insere(c,deuCerto1);
            
        }while(deuCerto && primeiro.position != c.position);
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
