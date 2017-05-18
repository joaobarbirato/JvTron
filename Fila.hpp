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

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da fila
template<class Gen>
class Fila{
private: //atributos privados
	int primeiro;
	int ultimo;
	int nElementos;
    Gen elementos[20000];
public: // atributos publicos
	Fila();
	~Fila();
	void Insere( Gen &, bool &);
	void Retira(Gen  &, bool &);
	bool Vazia() const;
    bool Cheia() const;
    int getNElementos();
    Gen* getDesenhoRastro();
};

//	Implementação dos métodos da Fila

//construtor
//Cria uma Fila com os atributos: primeiro, ultimo e numero de Elementos
template<class Gen>
Fila<Gen>::Fila(){
	ultimo = 0;
	primeiro = 0;
	nElementos = 0;
};
//fim destrutor

//Vazia()
//verifica se a Fila está vazia ou não
//retorna true se estiver, false se não estiver
template<class Gen>
bool Fila<Gen>::Vazia() const {
	if(nElementos == 0)
		return true;
	return false;
};
//fim Vazia()

//Cheia()
//verifica se a Fila está cheia ou não
//retorna true se estiver, false se não estiver
template<class Gen>
bool Fila<Gen>::Cheia() const {
	if(nElementos == 20000)
		return true;
	return false;
};
//fim Cheia()

//Insere()
//recebe por referência X do tipo Gen e deuCerto do tipo boolean
//se a Fila não estiver cheia, entao um elemento é inserido
template<class Gen>
void Fila<Gen>::Insere( Gen & x, bool& deuCerto){

	if(Cheia())
        deuCerto=false;
    else{
        deuCerto=true;
        nElementos++;
        elementos[ultimo]= x;
        if(ultimo==nElementos-1){
            ultimo=0;
        }
        else{
            ultimo++;
        }
    }
};
//fim Insere

//Retira()
////recebe por referência X do tipo Gen e deuCerto do tipo boolean
//se a Fila não estiver vazia, entao um elemento é retirado
template<class Gen>
void Fila<Gen>::Retira(Gen &x, bool & deuCerto){
	if(Vazia()){
		deuCerto = false;
    }
    else{
        deuCerto=true;
        nElementos--;
        x=elementos[primeiro];
        if(primeiro==nElementos-1){
            primeiro=0;
        }
        else{
            primeiro++;
        }
    }
};
//fim Retira()

//Destrutor
//Retira elemento por elemento da fila, até que fique vazia e seja destruida
template<class Gen>
Fila<Gen>::~Fila(){
	Gen x;
	bool deuCerto = true;
	while(!Vazia()){
 		Retira(x, deuCerto);
	}
};
//fim destrutor

//getNElementos()
//retorna o numero de elementos da fila
template<class Gen>
int Fila<Gen>::getNElementos(){
    return nElementos;

};
//fim getNElementos()

//getDesenhoRastro()
//retorna os elementos da rastro da moto
template<class Gen>
Gen* Fila<Gen>::getDesenhoRastro(){
    return elementos;
};
//fim getDesenhoRastro()
