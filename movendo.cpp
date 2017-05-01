#include<SFML/Graphics.hpp>
#include<iostream>


int main (){
	
	sf::RenderWindow window(sf::VideoMode(800,600),"SFML tutorial",sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(50.0f,20.0f)); // retangulo para a moto

    
    //textura para a moto
    sf::Texture playert;  
    playert.loadFromFile("boo.png");
	player.setTexture(&playert);
	
    
    
    sf::Vertex vertex[10000]; //esse vai ser o tipo da pilha q vai ser usado
    int i=0,j=0; // contadores para rodar o vetor e adicionar por onde ele passa
    int x=0,y=10; // valores para acertar o ratro confome a virada da moto
    
    
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
			}
		
              
                
                
		}
		if (evnt.type == sf::Event::KeyReleased )
        {
            //caso a pessoa aperte o A
            if (evnt.key.code == sf::Keyboard::A){
                //a moto estava antes em qual rotação ?
                
                if(player.getRotation() == 270){
                    y=-10;
                    x=10;
                    player.setRotation(180);
                    player.setPosition(player.getPosition().x , player.getPosition().y - 30 );
                }
                
                if(player.getRotation() == 90){
                    y=10;
                    x=0;
                    player.setRotation(0);
                    player.setPosition(player.getPosition().x - 10,player.getPosition().y + 20);
                }
                //a moto não pode virar para o oposto - bug tem q verificar no proximo
                if(player.getRotation() != 0){
                    player.move(-1.0f,0.0f);
                    
                }
            }
            //caso a pessoa aperte o S
           if (evnt.key.code == sf::Keyboard::S){
                //a moto estava antes em qual rotação ?
                if(player.getRotation() == 0){
                    x=10;
                    y=-40;
                    player.setRotation(270);
                    player.setPosition(player.getPosition().x - 10,player.getPosition().y+50);
                }if(player.getRotation() == 180){
                    x=-10;
                    y=30;
                    player.setRotation(90);
                    player.setPosition(player.getPosition().x + 20 ,player.getPosition().y - 40);
                    
                }
                //a moto não pode virar para o oposto - bug tem q verificar no proximo
                if(player.getRotation() != 90){
                    player.move(0.0f,1.0f);
                }
                
               
            }
            //caso a pessoa aperte o D
            if (evnt.key.code == sf::Keyboard::D){
                //a moto estava antes em qual rotação ?
                if(player.getRotation() == 270){
                    y=10;
                    x=0;
                    player.setRotation(0);
                    player.setPosition(player.getPosition().x + 10,player.getPosition().y - 50);
                }if(player.getRotation() == 90){
                    y=10;
                    x=0;
                    player.setRotation(0);
                    player.setPosition(player.getPosition().x - 10,player.getPosition().y + 40);
                }
                 //a moto não pode virar para o oposto - bug tem q verificar no proximo
                if(player.getRotation() != 180){
                    player.move(1.0f,0.0f);
                }
            }   
            //caso a pessoa aperte o D
            if (evnt.key.code == sf::Keyboard::W){
                //a moto estava antes em qual rotação ?
                if(player.getRotation() == 0){
                    x=-10;
                    y=+50;
                    player.setRotation(90);
                    player.setPosition(player.getPosition().x + 10,player.getPosition().y - 40 );
                } if(player.getRotation() == 180){
                    x=-10;
                    y=30;
                    player.setRotation(90);
                    player.setPosition(player.getPosition().x + 20 ,player.getPosition().y - 40);
                    
                }
                //a moto não pode virar para o oposto - bug tem q verificar no proximo
                if(player.getRotation() != 270){
                    player.move(0.0f,-1.0f);
                }
                
            }
            
        }
		//adiciona as posições que ela passa, menos a igual q a anterior
		if(i<10000 && vertex[i-1].position!=player.getPosition() ){
           vertex[i].position=player.getPosition();
           vertex[i].position.y+=y;
           vertex[i].position.x+=x;
           vertex[i].color = sf::Color(0,255,255);
           i++;
        }
        //desenha na tela o ratro e a moto
        window.draw(vertex,10000,sf::Points);
        window.draw(player);
        window.display();
        //limpa a tela 
        window.clear();
	
	
	}
	return 0;
}

