#include <iostream>
#include "Tela.hpp"

#include <SFML/Graphics.hpp>

class Regras : public Tela{
private:
	const int maxNumeroItens;
	int numeroItem;
	float largura, altura, centrox, centroy;
	sf::Font fonte;
	sf::Text *botao;
	sf::Text titulo;
	sf::Color cor;
public:
	Regras(float larg, float alt, sf::Color vcor);
	~Regras();
	virtual int Run(sf::RenderWindow &App);
	int ItemApertado();
	sf::Vector2f getCentro() const;
	void desenha(sf::RenderWindow &) const;
};

Regras::Regras(float larg, float alt, sf::Color vcor): maxNumeroItens(1){
	std::string texto[maxNumeroItens] = {"Voltar"};
	numeroItem = 0;
	botao = new sf::Text[maxNumeroItens];
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;
	cor = vcor;

	if (!fonte.loadFromFile("Tr2n.ttf")){}
	// inicializando titulo
	titulo.setCharacterSize(100);
	titulo.setString("SOBREVIVA");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*2.90, centroy-altura*1/3 + titulo.getCharacterSize() - 10));
	titulo.setFillColor(cor);

	//inicializando botoes
	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(40);

		if(i == 0)
			botao[i].setFillColor(cor);
		else
			botao[i].setFillColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(centrox - botao[i].getCharacterSize()*1.95, (altura-100)*2/3 + altura/(maxNumeroItens+1)/4*i-20));
	}

}

Regras::~Regras(){ delete botao; };

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
						switch(ItemApertado()){
                            case 0:
                            	return (0);
                                break;
                        }
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
    	sf::Vertex(sf::Vector2f(50, 50), cor),
	    sf::Vertex(sf::Vector2f(50, altura - 50), cor)
	};
	sf::Vertex vertDir[] =	{
	    sf::Vertex(sf::Vector2f(largura - 50, 50), cor),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), cor)
	};
	sf::Vertex horCima[] =	{
	    sf::Vertex(sf::Vector2f(50, 50), cor),
	    sf::Vertex(sf::Vector2f(largura - 50, 50), cor)
	};
	sf::Vertex horBaixo[] =	{
	    sf::Vertex(sf::Vector2f(50, altura - 50), cor),
	    sf::Vertex(sf::Vector2f(largura - 50, altura - 50), cor)
	};
    App.clear();
	App.draw(titulo);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
	App.draw(vertEsq, 2, sf::Lines);
	App.draw(vertDir, 2, sf::Lines);
	App.draw(horCima, 2, sf::Lines);
	App.draw(horBaixo, 2, sf::Lines);
};

int Regras::ItemApertado(){ return numeroItem; };