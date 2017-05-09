#include<SFML/Graphics.hpp>
#include<iostream>


int main (){
	
	sf::RenderWindow window(sf::VideoMode(800,600),"SFML tutorial",sf::Style::Close | sf::Style::Resize);
	sf::Sprite player[4]; // retangulo para a moto
    sf::Sprite moto;
    
    //textura para a moto
    sf::Texture playert;
    sf::Texture playert2;
    sf::Vertex vertex[10000]; //esse vai ser o tipo da pilha q vai ser usado
    int i=0,j=0; // contadores para rodar o vetor e adicionar por onde ele passa
    int x=0,y=0; // valores para acertar o ratro confome a virada da moto
    
    playert2.loadFromFile("direita.png");
    player[0].setTexture(playert2);
    playert.loadFromFile("cima.png");
    player[1].setTexture(playert);
    playert2.loadFromFile("esquerda.png");
    player[2].setTexture(playert2);
    playert.loadFromFile("baixo.png");
    player[3].setTexture(playert);
	while(window.isOpen()){
	
		sf::Event evnt;
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
		
		if (evnt.type == sf::Event::KeyReleased )
        {
                
            
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
	
	
	}
	return 0;
}

