/*
	JvTron: Trabalho 1
	Departamento de Computação
	UFSCar Universidade Federal de São Carlos
	Disciplina: Estrutura de Dados
	Professor: Roberto Ferrari
	Aluno(a):								RA:
		João Gabriel Melo Barbirato			726546
		Leonardo de Oliveira Peralta		726556
		Gabrieli Santos						726523
    
	Controle de Versão: https://github.com/joaobarbirato/JvTron
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tela.hpp"

// Estrutura do Menu
class Menu : public Tela{
private:
	// atributos privados
	const int maxNumeroItens; // número máximo de botões
	int numeroItem; // número do item pressionado
	float largura, altura, centrox, centroy; // medidas da tela
	sf::Font fonte;
	sf::Text titulo;
	sf::Text *botao; // vetor de botões

	// métodos privados
	void MovaParaCima();
	void MovaParaBaixo();
	void desenha(sf::RenderWindow &) const;
	int ItemApertado();
public: // métodos privados
	Menu(float larg, float alt);
	~Menu();
	virtual int Run(sf::RenderWindow& App);
};

// Implementação dos métodos do menu

// Construtor
// Recebe como parâmetro a largura e altura (utiliza-se as medidas da janela principal da aplicação)
// Configuração inicial de atributos
Menu::Menu(float larg, float alt): maxNumeroItens(3){
	std::string texto[maxNumeroItens] = {"Jogar", "Regras", "Sair"}; // texto para os botões
	numeroItem = 0; // seleciona-se o primeiro item

	// configuração das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	botao = new sf::Text[maxNumeroItens]; // alocação dinâmica do tamanho do vetor de botões

	if (!fonte.loadFromFile("Tr2n.ttf")){}// carregar fonte selecionada	

	// inicializando titulo
	titulo.setCharacterSize(90);
	titulo.setString("JvTron");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*1.95, centroy-altura*1/3 + titulo.getCharacterSize() - 100));
	titulo.setFillColor(sf::Color(0,255,255));

	//inicializando botoes
	for(int i = 0; i < maxNumeroItens; i++){ 
		botao[i].setFont(fonte);
		botao[i].setCharacterSize(40);
		if(i == 0)
			botao[i].setFillColor(sf::Color(0,255,255));
		else
			botao[i].setFillColor(sf::Color::White);
		botao[i].setString(texto[i]);
		botao[i].setPosition(sf::Vector2f(centrox - botao[i].getCharacterSize()*1.95, (altura-100)*2/3 + altura/(maxNumeroItens+1)/2.5*i - 80));
	}
}
// fim Construtor

// Destrutor
// Deleta vetor de botões
Menu::~Menu(){ delete botao; }; // fim Destrutor

// Run
// Recebe por referência a janela da biblioteca gráfica
int Menu::Run(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event; // eventos de jogo
	bool Running = true;
	int alpha = 0;
	while (Running){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){
				return (-1);
			}
			// ao pressionar botões
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){ // 
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
                            	return (4);
                                break;
                            case 2:
                                return (-1);
                                break;
                        }
                        break;
					default:
						break;
				}
			}
		}// fim loop de eventos

		// desenhar coisas na tela
		App.clear();
		desenha(App); // chamada de método desenha
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}
// fim Run

// Desenha
// Método que desenha na tela alguns atributos
void Menu::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, altura/3));
    linhas.setFillColor(sf::Color::Black);
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(sf::Color(0,255,255));
    linhas.setSize(sf::Vector2f(largura-100, altura*2/3 -50));

    // desenha na janela
    App.clear();
	App.draw(titulo);
	App.draw(linhas);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
};
// fim Desenha

// MovaParaCima
// Move a seleção de botão para cima
void Menu::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Menu::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setFillColor(sf::Color(0,255,255));
	}
};
// fim MovaParaBaixo

// ItemApertado
// Retorna o número do botão selecionado
int Menu::ItemApertado(){ return numeroItem; };
// fim ItemApertado