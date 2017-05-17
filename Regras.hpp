#include <iostream>
#include "Tela.hpp"

#include <SFML/Graphics.hpp>

class Regras : public Tela{
private:
	const int maxNumeroItens;
	const int maxNumeroInfo;
	int numeroItem;
	float largura, altura, centrox, centroy;
	sf::Text titulo;
	sf::Font fonte;
	sf::Text *botao;
	sf::Text *infos;
	sf::RectangleShape *tecla;
public:
	Regras(float larg, float alt);
	~Regras();
	virtual int Run(sf::RenderWindow &App);
	int ItemApertado();
	sf::Vector2f getCentro() const;
	void desenha(sf::RenderWindow &) const;
};

Regras::Regras(float larg, float alt): maxNumeroItens(1), maxNumeroInfo(8){
	std::string texto[maxNumeroItens] = {"Voltar"};
	std::string instrucoes[maxNumeroInfo] = {
		"w", "i", "a", "j",
		"s", "k", "d", "l"
	};

	numeroItem = 0;

	tecla = new sf::RectangleShape[maxNumeroInfo];
	botao = new sf::Text[maxNumeroItens];
	infos = new sf::Text[maxNumeroInfo];

	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("Tr2n.ttf")){}
	// inicializando titulo
	titulo.setCharacterSize(100);
	titulo.setString("SOBREVIVA");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*2.90, centroy-altura*1/3 + titulo.getCharacterSize() - 50));
	titulo.setFillColor(sf::Color(0,255,255));

	// inicializando botoes
	botao[0].setFont(fonte);
	botao[0].setCharacterSize(40);
	botao[0].setFillColor(sf::Color(0,255,255));
	botao[0].setString(texto[0]);
	botao[0].setPosition(sf::Vector2f(centrox - botao[0].getCharacterSize()*1.95, altura-100));

	// inicializando infos
	int jA = 0, jL = 0;
	for(int i=0; i < maxNumeroInfo; i++){
		infos[i].setString(instrucoes[i]);
		infos[i].setFont(fonte);
		infos[i].setCharacterSize(35);
		tecla[i].setSize(sf::Vector2f(50,50));
		tecla[i].setFillColor(sf::Color::Black);
		tecla[i].setOutlineThickness(1);

		if(i%2==0){// disposicao das infos da moto azul
			infos[i].setFillColor(sf::Color(0,255,255));
			tecla[i].setOutlineColor(sf::Color(0,255,255));
			switch(i){
				case 0:
					infos[i].setPosition(sf::Vector2f(100 + largura/(maxNumeroInfo+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroInfo+1) ));
					tecla[i].setPosition(sf::Vector2f(90 + largura/(maxNumeroInfo+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroInfo+1) ));
					break;
				default:
					infos[i].setPosition(sf::Vector2f(100 + jA*largura/(maxNumeroInfo+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroInfo+1) ));
					tecla[i].setPosition(sf::Vector2f(90 + jA*largura/(maxNumeroInfo+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroInfo+1) ));
					jA++;
					break;
			}
		}else{// disposicao das infos da moto laranja
			infos[i].setFillColor(sf::Color(255,60,0));
			tecla[i].setOutlineColor(sf::Color(255,60,0));
			switch(i){
				case 1:
					infos[i].setPosition(sf::Vector2f(centrox + 105 + largura/(maxNumeroInfo+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroInfo+1) ));
					tecla[i].setPosition(sf::Vector2f(centrox + 85 + largura/(maxNumeroInfo+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroInfo+1) ));
					break;
				default:
					infos[i].setPosition(sf::Vector2f(centrox + 100 + jL*largura/(maxNumeroInfo+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroInfo+1) ));
					tecla[i].setPosition(sf::Vector2f(centrox + 85 + jL*largura/(maxNumeroInfo+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroInfo+1) ));
					jL++;
					break;
			}
		}
	}

}

Regras::~Regras(){ 
	delete botao;
	delete infos;
};

int Regras::Run(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event;
	bool Running = true;
	int alpha = 0;
	while (Running){ // gameloop
		//Verifying events
		while (App.pollEvent(Event)){ // eventloop
			// App closed
			if (Event.type == sf::Event::Closed){
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
					case sf::Keyboard::Return:
						return (0);
                        break;
					default:
						break;
				}
			}
			if (Event.type == sf::Event::Resized){
			    App.setView(sf::View(sf::FloatRect(0, 0, Event.size.width, Event.size.height)));
                //resizeView(window, view);
                printf("Nova janela com width: %i e com height: %i \n",Event.size.width,Event.size.height);
                break;
            }
		}// fim eventloop
		//When getting at alpha_max, we stop modifying the sprite
//      view.setCenter(Regras.getCentro());
//      App.setView(view);
		App.clear();
		desenha(App);
        App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}

void Regras::desenha(sf::RenderWindow & App) const{
	sf::Vertex vertEsq[] =	{
    	sf::Vertex(sf::Vector2f(50, 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(50, altura - 50), sf::Color(0,255,255))
	};
	sf::Vertex vertDir[] =	{
	    sf::Vertex(sf::Vector2f(largura - 50, 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), sf::Color(0,255,255))
	};
	sf::Vertex horCima[] =	{
	    sf::Vertex(sf::Vector2f(50, 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, 50), sf::Color(0,255,255))
	};
	sf::Vertex horBaixo[] =	{
	    sf::Vertex(sf::Vector2f(50, altura - 50), sf::Color(0,255,255)),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), sf::Color(0,255,255))
	};

    App.clear();
	App.draw(titulo);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
	for(int i = 0; i < maxNumeroInfo; i++){
		App.draw(tecla[i]);
		App.draw(infos[i]);
	}
	App.draw(vertEsq, 2, sf::Lines);
	App.draw(vertDir, 2, sf::Lines);
	App.draw(horCima, 2, sf::Lines);
	App.draw(horBaixo, 2, sf::Lines);
};

int Regras::ItemApertado(){ return numeroItem; };