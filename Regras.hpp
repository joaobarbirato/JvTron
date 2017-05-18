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
#include "Tela.hpp"

#include <SFML/Graphics.hpp>

class Regras : public Tela{
private: 
	// atributos privados
	const int maxNumeroTeclas; // numero de teclas
	float largura, altura, centrox, centroy; // variáveis pra guardar medidas da tela utilizada
	sf::Text titulo;
	sf::Font fonte;
	sf::Text botao;
	sf::Text *infos; // vetor de texto para teclas
	sf::RectangleShape *tecla; // vetor de teclas

	// métodos privados
	void desenha(sf::RenderWindow &) const;
public: // métodos públicos
	Regras(float larg, float alt);
	~Regras();
	virtual int Run(sf::RenderWindow &App);
};

// Implementação dos métodos

// Construtor
// Inicializa e configura os atributos
Regras::Regras(float larg, float alt):  maxNumeroTeclas(8){
	std::string texto = {"Voltar"}; // texto do botão
	std::string instrucoes[maxNumeroTeclas] = { // informacoes sobre as teclas
		"w", "i", "a", "j",
		"s", "k", "d", "l"
	};

	// alocação de posições
	tecla = new sf::RectangleShape[maxNumeroTeclas]; // vetor de teclas
	infos = new sf::Text[maxNumeroTeclas]; // vetor de informações

	// variaveis das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;

	if (!fonte.loadFromFile("Tr2n.ttf")){} // fonte das letras

	// inicializando titulo
	titulo.setCharacterSize(100);
	titulo.setString("SOBREVIVA");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*2.90, centroy-altura*1/3 + titulo.getCharacterSize() - 50));
	titulo.setFillColor(sf::Color(0,255,255));

	// inicializando botoes
	botao.setFont(fonte);
	botao.setCharacterSize(40);
	botao.setFillColor(sf::Color(0,255,255));
	botao.setString(texto);
	botao.setPosition(sf::Vector2f(centrox - botao.getCharacterSize()*1.95, altura-100));

	// inicializando infos
	int jA = 0, jL = 0;
	for(int i=0; i < maxNumeroTeclas; i++){
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
				case 0: // tecla w
					infos[i].setPosition(sf::Vector2f(100 + largura/(maxNumeroTeclas+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroTeclas+1) ));
					tecla[i].setPosition(sf::Vector2f(90 + largura/(maxNumeroTeclas+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroTeclas+1) ));
					break;
				default: // a, s, d
					infos[i].setPosition(sf::Vector2f(100 + jA*largura/(maxNumeroTeclas+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroTeclas+1) ));
					tecla[i].setPosition(sf::Vector2f(90 + jA*largura/(maxNumeroTeclas+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroTeclas+1) ));
					jA++;
					break;
			}
		}else{// disposicao das infos da moto laranja
			infos[i].setFillColor(sf::Color(255,60,0));
			tecla[i].setOutlineColor(sf::Color(255,60,0));
			switch(i){
				case 1: // tecla i
					infos[i].setPosition(sf::Vector2f(centrox + 105 + largura/(maxNumeroTeclas+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroTeclas+1) ));
					tecla[i].setPosition(sf::Vector2f(centrox + 85 + largura/(maxNumeroTeclas+1), centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + altura/(maxNumeroTeclas+1) ));
					break;
				default: // j, k, l
					infos[i].setPosition(sf::Vector2f(centrox + 100 + jL*largura/(maxNumeroTeclas+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroTeclas+1) ));
					tecla[i].setPosition(sf::Vector2f(centrox + 85 + jL*largura/(maxNumeroTeclas+1) , centroy-altura*1/3 + (titulo.getCharacterSize() + 90) + 2*altura/(maxNumeroTeclas+1) ));
					jL++;
					break;
			}
		}
	}
}
// fim construtor

// Destrutor
// Deleta os ponteiros declarados
Regras::~Regras(){ 
	delete infos;
};

// Run
// Recebe por referência a janela da biblioteca gráfica
int Regras::Run(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event; // eventos de jogo
	bool Running = true;
	while (Running){ // loop da tela
		// verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){
				return (-1);
			}
			// evento de 
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
					case sf::Keyboard::Return:
						return (0); // retorna à tela de menu
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
void Regras::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color::Black);
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(sf::Color(0,255,255));
    linhas.setSize(sf::Vector2f(App.getSize().x-100, App.getSize().y*4/5 -100));

    // desenha na janela
    App.clear();
	App.draw(titulo);
	App.draw(botao);
	for(int i = 0; i < maxNumeroTeclas; i++){
		App.draw(tecla[i]);
		App.draw(infos[i]);
	}
	App.draw(linhas);
};
// fim Desenha