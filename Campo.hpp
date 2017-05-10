#include <iostream>
#include "Tela.hpp"

#include <SFML/Graphics.hpp>

class Campo : public Tela{
private:
    sf::Sprite player[4]; // retangulo para a moto
    sf::Sprite moto;
    //textura para a moto
    sf::Texture playert;
    sf::Texture playert2;
    sf::Vertex vertex[10000]; //esse vai ser o tipo da pilha q vai ser usado
    int i=0,j=0; // contadores para rodar o vetor e adicionar por onde ele passa
    int x=0,y=0; // valores para acertar o ratro confome a virada da moto
public:
	Campo(void);
	virtual int Run(sf::RenderWindow &App);
	void desenha(sf::RenderWindow &) const;
};

Campo::Campo(void){
    playert2.loadFromFile("motoMovendo/direita.png");
    player[0].setTexture(playert2);
    playert.loadFromFile("motoMovendo/cima.png");
    player[1].setTexture(playert);
    playert2.loadFromFile("motoMovendo/esquerda.png");
    player[2].setTexture(playert2);
    playert.loadFromFile("motoMovendo/baixo.png");
    player[3].setTexture(playert);

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
                            if(j == 1){
                                player[2].setPosition(sf::Vector2f(moto.getPosition().x  + (moto.getTexture()->getSize().x)/2 - player[2].getTexture()->getSize().x   ,moto.getPosition().y - (player[2].getTexture()->getSize().y)/2 + moto.getTexture()->getSize().y  ));
                            }if(j == 3){
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
        if (Event.type == sf::Event::KeyReleased ){
            //caso a pessoa aperte o A
            if (Event.key.code == sf::Keyboard::A){
                //a moto estava antes em qual rotação ?
                moto.move(-1.0f,0.0f);
            }
            //caso a pessoa aperte o S
            if (Event.key.code == sf::Keyboard::S){
                //a moto estava antes em qual rotação ?
                moto.move(0.0f,1.0f);    
            }
            //caso a pessoa aperte o D
            if (Event.key.code == sf::Keyboard::D){
                //a moto estava antes em qual rotação ?
                moto.move(1.0f,0.0f);
            }   
            //caso a pessoa aperte o D
            if (Event.key.code == sf::Keyboard::W){
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
        desenha(App);
        App.draw(vertex,10000,sf::Points);
        App.draw(moto);
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