#include "Fila.h"
#include <iostream>
using namespace std;
/*
	Implementação dos métodos da Fila
*/
Fila::Fila(){ // Cria()
	ultimo = NULL;
	primeiro = NULL;

};

bool Fila::Vazia() const {
	if(this->primeiro == NULL)
		return true;
	return false;
};

void Fila::Insere(const char & x, bool &  deuCerto){
	NodePtr PAux = new Node;
	if(PAux == NULL)
		deuCerto = false;
	else{
		deuCerto = true;
		PAux->info = x;
		PAux->next = NULL;
		if(Vazia())
			this->primeiro = PAux;
		else
			this->ultimo->next = PAux;
		this->ultimo = PAux;
	}
};

void Fila::Retira(char & x, bool & deuCerto){
	NodePtr PAux;
	if(Vazia()){
		deuCerto = false;
	}else{
		deuCerto = true;
		x = this->primeiro->info;
		PAux = this->primeiro;
		this->primeiro = this->primeiro->next;
		if(this->primeiro == NULL)
			this->ultimo = NULL;
		nElementos--;
		delete PAux;
	}
};
	
Fila::~Fila(){ // Destroi()
	char x;
	bool deuCerto = true;
	while(!this->Vazia()){
		this->Retira(x, deuCerto);
	}
};