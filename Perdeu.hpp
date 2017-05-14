#include <iostream>
#include "Tela.hpp"

#include <SFML/Graphics.hpp>

class Perdeu : public Tela{
private:
	const int maxNumeroItens;
	int numeroItem;
	float largura, altura, centrox, centroy;
	sf::Font fonte;
	sf::Text *botao;
	sf::Text titulo;
public:
	Perdeu(float larg, float alt);
	~Perdeu();
	virtual int Run(sf::RenderWindow &App);
	void MovaParaCima();
	void MovaParaBaixo();
	int ItemApertado();
	sf::Vector2f getCentro() const;
	void desenha(sf::RenderWindow &) const;
};

Perdeu::Perdeu(float larg, float alt): maxNumeroItens(2){
	std::string texto[maxNumeroItens] = {"Jogar novamente", "Sair"};
	numeroItem = 0;
	botao = new sf::Text[maxNumeroItens];
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("TRON.TTF"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
	}
	// inicializando titulo
	titulo.setCharacterSize(70);
	titulo.setString("Perdeu!");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*3, centroy-altura*1/3 + titulo.getCharacterSize() - 10));
	titulo.setFillColor(sf::Color(0,255,255));

	//inicializando botoes
	for(int i = 0; i < maxNumeroItens; i++){
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(20);

		if(i == 0)
			botao[i].setFillColor(sf::Color(0,255,255));
		else
			botao[i].setFillColor(sf::Color::White);

		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(centrox - botao[i].getCharacterSize()*3, (altura-100)*2/3 + altura/(maxNumeroItens+1)/4*i));
	}

}

Perdeu::~Perdeu(){ delete botao; };

int Perdeu::Run(sf::RenderWindow &App){
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
					case sf::Keyboard::Up:
                        MovaParaCima();
                        break;
                    case sf::Keyboard::Down:
                        MovaParaBaixo();
                        break;
					case sf::Keyboard::Return:
						switch(ItemApertado()){
                            case 0:
                            	return (1);
                                break;
                            case 1:
                                return (-1);
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
//      view.setCenter(Perdeu.getCentro());
//      App.setView(view);
		App.clear();
		desenha(App);
        App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}

void Perdeu::desenha(sf::RenderWindow & App) const{
	//Clearing screen
    App.clear();
	App.draw(titulo);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
};

void Perdeu::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};

void Perdeu::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};
int Perdeu::ItemApertado(){ return numeroItem; };