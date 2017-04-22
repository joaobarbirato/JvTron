/*
g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
*/
#include <SFML/Graphics.hpp>

int main(){
	// criar janela
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::White);
	window.setFramerateLimit(60);

	// gameloop
    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){ // eventloop

        	switch(event.type){
        		case sf::Event::Closed: //fechar a janela de jogo
        			window.close();
        			break;
/*
        		case sf::Event::LostFocus: // sair da tela = pause
        			mygame.pause();
        			break;
        		case sf::Event::GainFocus: // voltar à tela = continua
        			mygame.resume();
        			break;
*/        		case sf::Event::KeyPressed:
        			switch(event.key.code){ // arrows
        				case sf::Keyboard::Left:
//        					shape.setFillColor(sf::Color::Green);
        					break;
        				case sf::Keyboard::Right:
//        					shape.setFillColor(sf::Color::Red);
        					break;
        				case sf::Keyboard::Up:
//        					shape.setFillColor(sf::Color::Yellow);
        					break;
        				case sf::Keyboard::Down:
//        					shape.setFillColor(sf::Color::Blue);
        					break;

        			}

        	}
        }// fim eventloop

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }// fim gameloop

    return 0;
}