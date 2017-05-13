#include "Fila.h"
#include <iostream>
using namespace std;
/*
	Implementação dos métodos da Fila
*/
Fila::Fila(){ // Cria()
	ultimo = NULL;
	primeiro = NULL;
	nElementos = 0;
};

bool Fila::Vazia() const {
	if(primeiro == NULL)
		return true;
	return false;
};

void Fila::Insere( sf::Vertex & x, bool& deuCerto){
	NodePtr PAux = new Node;
	if(PAux == NULL)
		deuCerto = false;
	else{
		deuCerto = true;
		PAux->info = x;
		PAux->next = NULL;
		if(Vazia()){
			primeiro = PAux;
            ultimo = PAux;
        }else{
            ultimo->next = PAux;
            ultimo = PAux;
            
        }
		nElementos++;
	}
};

void Fila::Retira(sf::Vertex & x, bool & deuCerto){
	NodePtr PAux = new Node;
	if(Vazia()){
		deuCerto = false;
	}else{
		deuCerto = true;
		x = primeiro->info;
		PAux = primeiro;
		primeiro = primeiro->next;
		if(primeiro == NULL)
			ultimo = NULL;
		delete PAux;
		nElementos--;
	}
};
	
Fila::~Fila(){ // Destroi()
	sf::Vertex x;
	bool deuCerto = true;
	while(!this->Vazia()){
		this->Retira(x, deuCerto);
	}
};

void Fila::RetiraAPartirDe(const int & n, bool & deuCerto){
	Fila F;
	sf::Vertex x;
	deuCerto = true;
	for(int i = 0; i < (nElementos - n + 1); i++){
		this->Retira(x, deuCerto);
//		cout << x << endl;
		if(!deuCerto){
			i = (nElementos-n+1);
		}else
			F.Insere(x, deuCerto);
	}
};

