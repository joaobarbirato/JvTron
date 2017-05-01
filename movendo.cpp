#include<SFML/Graphics.hpp>
#include<iostream>


int main (){
	
	sf::RenderWindow window(sf::VideoMode(800,600),"SFML tutorial",sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(20.0f,20.0f));
    sf::RectangleShape rastro(sf::Vector2f(20.0f,20.0f));
    sf::Texture playert;
    playert.loadFromFile("boo.png");
	player.setTexture(&playert);
	rastro.setFillColor(sf::Color::Green);
	int direcao=0;
    
    sf::Vector2f vetor[1000];
    int i=0,j=0;    
	while(window.isOpen()){
	
		sf::Event evnt;
		while(window.pollEvent(evnt)){
			switch(evnt.type){
			
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					printf("Nova janela com width: %i e com height: %i \n",evnt.size.width,evnt.size.height);
					break;

				case sf::Event::TextEntered:
					if(evnt.text.unicode < 128)
						printf("%c",evnt.text.unicode);			
                    break;
			}
			if (evnt.type == sf::Event::KeyPressed)
                {
                    if (evnt.key.code == sf::Keyboard::A)
                        player.move(-0.1f,0.0f);
                    
                    if (evnt.key.code == sf::Keyboard::S)
                        player.move(0.0f,0.1f);
                    
                    if (evnt.key.code == sf::Keyboard::D)
                        player.move(0.1f,0.0f);
                    
                    if (evnt.key.code == sf::Keyboard::W)
                        player.move(0.0f,-0.1f);
                    
                }
              
                
                
		}
		if (evnt.type == sf::Event::KeyReleased )
        {
            if (evnt.key.code == sf::Keyboard::A){
                player.move(-0.1f,0.0f);
            }
            if (evnt.key.code == sf::Keyboard::S)
                player.move(0.0f,0.1f);
            
            if (evnt.key.code == sf::Keyboard::D)
                player.move(0.1f,0.0f);
            
            if (evnt.key.code == sf::Keyboard::W)
                player.move(0.0f,-0.1f);
            
            
        }
		window.clear();
		if(i<1000 && vetor[i-1]!=player.getPosition() ){	
           vetor[i]=player.getPosition();
           i++;
        }
        for(j=0;j<i;j++){  
            rastro.setPosition(vetor[j]);
            window.draw(rastro);
          }
        window.draw(player);
        window.display();
	
	
	
	}
	return 0;
}

