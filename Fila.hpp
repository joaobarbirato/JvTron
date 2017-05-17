/*
	Cabeçalho da Fila
*/

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da fila
template<class Gen>
class Fila{
private:
	int primeiro;
	int ultimo;
	int nElementos;
    Gen elementos[20000];
public:
	Fila();
	~Fila();
	void Insere( Gen &, bool &);
	void Retira(Gen  &, bool &);
//	void RetiraAteElemento(Gen & x, bool & deuCerto);
	bool Vazia() const;
    bool Cheia() const;
    int getNElementos();
    Gen* getDesenhoRastro();
};
/*
	Implementação dos métodos da Fila
*/
template<class Gen>
Fila<Gen>::Fila(){ // Cria()
	ultimo = 0;
	primeiro = 0;
	nElementos = 0;
};
template<class Gen>
bool Fila<Gen>::Vazia() const {
	if(nElementos == 0)
		return true;
	return false;
};

template<class Gen>
bool Fila<Gen>::Cheia() const {
	if(nElementos == 20000)
		return true;
	return false;
};

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
        }else{
            ultimo++;
        }
        
    }
};


template<class Gen>
void Fila<Gen>::Retira(Gen &x, bool & deuCerto){
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
	

template<class Gen>
Fila<Gen>::~Fila(){ // Destroi()
	Gen x;
	bool deuCerto = true;
	while(!Vazia()){
// 		Retira(x, deuCerto);
	}
};

/*
template<class Gen>
void Fila<Gen>::RetiraAteElemento(Gen & x, bool & deuCerto){
	
	Gen y;
    do{
        Retira(y,deuCerto);
    }while(y.position!=x.position);

};
*/
template<class Gen>
Gen* Fila<Gen>::getDesenhoRastro(){
    
    return elementos;
};

template<class Gen>
int Fila<Gen>::getNElementos(){
    return nElementos;
    
};
