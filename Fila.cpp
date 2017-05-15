#include "Fila.h"
#include <iostream>
using namespace std;
/*
	Implementação dos métodos da Fila
*/
Fila::Fila(){ // Cria()
	ultimo = 0;
	primeiro = 0;
	nElementos = 0;
};

bool Fila::Vazia() const {
	if(nElementos == 0)
		return true;
	return false;
};
bool Fila::Cheia() const {
	if(nElementos == 20000)
		return true;
	return false;
};
void Fila::Insere( sf::Vertex & x, bool& deuCerto){
	
	if(Cheia())
        deuCerto=false;
    else{
        deuCerto=true;
        nElementos++;
        elementos[ultimo]= x;
        if(ultimo==nElementos-1){
            ultimo=0;
        }else{
            ultimo++;
        }
        
    }
};

void Fila::Retira(sf::Vertex &x, bool & deuCerto){
	if(Vazia()){
		deuCerto = false;
    }else{
        deuCerto=true;
        nElementos--;
        x=elementos[primeiro];
        if(primeiro==nElementos-1){
            primeiro=0;
        }else{
            primeiro++;
        }
    }
        
};
	
Fila::~Fila(){ // Destroi()
	sf::Vertex x;
	bool deuCerto = true;
	while(!Vazia()){
// 		Retira(x, deuCerto);
	}
};

void Fila::RetiraAteElemento(sf::Vertex & x, bool & deuCerto){
	
	sf::Vertex y;
    do{
        Retira(y,deuCerto);
    }while(y.position!=x.position);

};

sf::Vertex* Fila::getDesenhoRastro(){
    
    return elementos;
};
int Fila::getNElementos(){
    return nElementos;
    
};
