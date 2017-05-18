/*
    JvTron: Trabalho 1
    Departamento de Computação
    UFSCar Universidade Federal de São Carlos
    Disciplina: Estrutura de Dados
    Professor: Roberto Ferrari
    Aluno(a):                               RA:
        João Gabriel Melo Barbirato         726546
        Leonardo de Oliveira Peralta        726556
        Gabrieli Santos                     726523

    Controle de Versão: https://github.com/joaobarbirato/JvTron
*/

#include <iostream>
#include "Tela.hpp"
#include <SFML/Graphics.hpp>

// Estrutura da tela Ganhou
class Ganhou : public Tela{
private:
	// atributos privados
	const int maxNumeroItens; // número máximo de botões
	int numeroItem; // número do item pressionado
	float largura, altura, centrox, centroy; // medidas da tela
	sf::Font fonte;
	sf::Text titulo;
	sf::Color cor;
	sf::Text *botao; // vetor de botões

	void MovaParaCima();
	void MovaParaBaixo();
	void desenha(sf::RenderWindow &) const;
	int ItemApertado();
public:
	// métodos privados
	Ganhou(float larg, float alt, sf::Color vcor);
	~Ganhou();
	virtual int Run(sf::RenderWindow &App);
};

// Construtor
// Recebe como parâmetros as dimensões da janela e a cor do ganhador
// Inicializa e configura os atributos
Ganhou::Ganhou(float larg, float alt, sf::Color vcor): maxNumeroItens(2){
	std::string texto[maxNumeroItens] = {"Jogar novamente", "Sair"}; // texto dos botões
	numeroItem = 0; // seleciona o primeiro item

	// configuração das medidas
	largura = larg;
	altura = alt;
	centrox = largura/2;
	centroy = altura/2;
	cor = vcor;

	botao = new sf::Text[maxNumeroItens]; // alocação de botões

	if (!fonte.loadFromFile("Tr2n.ttf")){} // carregar fonte selecionada
	// inicializando titulo
	titulo.setCharacterSize(100);
	titulo.setString("Ganhou");
	titulo.setFont(fonte);
	titulo.setPosition(sf::Vector2f(centrox - titulo.getCharacterSize()*1.95, centroy-altura*1/3 + titulo.getCharacterSize() - 10));
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
		botao[i].setPosition(sf::Vector2f(centrox - botao[i].getCharacterSize()*5, (altura-100)*2/3 + altura/(maxNumeroItens+1)/4*i-20));
	}
}
// fim Construtor

// Destrutor
// Deleta vetor de botões
Ganhou::~Ganhou(){ delete botao; }; // fim Destrutor

// Run
// Recebe por referência a janela da biblioteca gráfica
int Ganhou::Run(sf::RenderWindow &App){
	// declaracao de variaveis
	sf::Event Event; // eventos do jogo
	bool Running = true;
	while (Running){ // loop da tela
		// Verificação de eventos
		while (App.pollEvent(Event)){ // loop de eventos
			if (Event.type == sf::Event::Closed){ // se fechar a tela
				return (-1); // fim jogo
			}
			// ao pressionar botões
			if (Event.type == sf::Event::KeyPressed){
				switch (Event.key.code){
					// navegar pelas opções
					case sf::Keyboard::Up:
                        MovaParaCima();
                        break;
                    case sf::Keyboard::Down:
                        MovaParaBaixo();
                        break;
                    // pressionar opção
					case sf::Keyboard::Return:
						switch(ItemApertado()){
                            case 0:
                            	return (1); // jogar novamente
                                break;
                            case 1:
                                return (-1); // sair
                                break;
                        }
                        break;
				}
			}
		}// fim loop de eventos

		// desenhar coisas na tela
		App.clear();
		desenha(App);
        App.display();
	} // fim loop da tela

	// não há como chegar até aqui mas, se acontecer, termine o programa.
	return (-1);
}
// fim Run

// Desenha
// Método que desenha na tela alguns atributos
void Ganhou::desenha(sf::RenderWindow & App) const{
	sf::RectangleShape linhas; // retângulo para linhas
	// configuração do retangulo
    linhas.setPosition(sf::Vector2f(50, 50));
    linhas.setFillColor(sf::Color::Black);
    linhas.setOutlineThickness(1);
    linhas.setOutlineColor(cor);
    linhas.setSize(sf::Vector2f(largura-100, altura -100));

    // desenha na janela
    App.clear();
    App.draw(linhas);
	App.draw(titulo);
	for(int i = 0; i < maxNumeroItens; i++){
		App.draw(botao[i]);
	}
};
// fim Desenha

// MovaParaCima
// Move a seleção de botão para cima
void Ganhou::MovaParaCima(){
	if(numeroItem - 1 >= 0){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem--;
		botao[numeroItem].setFillColor(cor);
	}
};
// fim MovaParaCima

// MovaParaBaixo
// Move a seleção de botão para baixo
void Ganhou::MovaParaBaixo(){
	if(numeroItem + 1 < maxNumeroItens){
		botao[numeroItem].setFillColor(sf::Color::White);
		numeroItem++;
		botao[numeroItem].setFillColor(cor);
	}
};
// fim MovaParaBaixo

// ItemApertado
// Retorna o número do botão selecionado
int Ganhou::ItemApertado(){ return numeroItem; };
// fim ItemApertado