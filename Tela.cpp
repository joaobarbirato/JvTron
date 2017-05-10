#include "Tela.h"

Tela::Tela(float vlargura, float valtura, float vtamanhoFonte): tamanhoFonte(vtamanhoFonte){
	this->largura = vlargura;
	this->altura = valtura;
	centrox = largura/2;
	centroy = altura/2;
	if(!fonte.loadFromFile("TRON.TTF")){}
	Tela::titulo.setFont(fonte);
	Tela::titulo.setString("JvTron");
	Tela::titulo.setCharacterSize(Tela::tamanhoFonte);
	Tela::titulo.setFillColor(sf::Color(0,255,255));
};

Tela::~Tela(){};

float Tela::getCx() const { return centrox; };
float Tela::getCy() const { return centroy; };
float Tela::getLargura() const {return largura;};
float Tela::getAltura() const {return altura;};
float Tela::getTFonte() const {return tamanhoFonte;};
sf::Font Tela::getFonte() const {return fonte;};
sf::Text Tela::getTitulo() const {return titulo;};