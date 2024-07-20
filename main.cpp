#include <iostream>
using namespace std;

struct noGerado {
	int senha;
	noGerado *prox;
};

struct noAtendido {
    int senha;
    noAtendido *prox;
};

struct senhasGeradas {
	noGerado *ini;
	noGerado *fim;
};

struct senhasAtendidas {
    noAtendido *ini;
    noAtendido *fim;
};

struct Lista{
    int guiche;
    senhasAtendidas *filaAtendida;
    Lista *prox;
};
// ----------------------- Senhas Geradas functions and returns -----------------------

senhasGeradas* initGer() { // iniciar senhas geradas
	senhasGeradas *sGer = new senhasGeradas;
	sGer->ini = NULL;
	sGer->fim = NULL;
	return sGer;
}

int isEmptyGer(senhasGeradas *sGer) { // verificador de null de senhas geradas
	return (sGer->ini == NULL);
}

void enfSenhaGer(senhasGeradas *sGer, int s) { // enfileirador de senhas geradas
	noGerado *no = new noGerado;
	no->senha = s;
	no->prox = NULL;
	if (isEmptyGer(sGer)) {
		sGer->ini = no;
	}
	else {
		sGer->fim->prox = no;
	}
	sGer->fim = no;
}

int contSenhas(senhasGeradas *sGer) { // contagem de senhas geradas
	int qtde = 0;
	noGerado *no;
	no = sGer->ini;
	while (no != NULL) {
		qtde++;
		no = no->prox;
	}
	return qtde;
}

int desSenhaGer(senhasGeradas *sGer) { // desempilhador de senhas geradas
	int res;
	if (isEmptyGer(sGer)) {
		res = -1;
	}
	else {
		noGerado *no = sGer->ini;
		res = no->senha;
		sGer->ini = no->prox;
		if (sGer->ini == NULL) {
			sGer->fim = NULL;
		}
	    free(no);	
	}
	return res;
}

int senhaVez(senhasGeradas *sGer) { // senha da vez
    int senha = 0;
	noGerado *no;
	no = sGer->ini;
	if (no != NULL) {
		senha = no->senha;
	}
	
	return senha;
}

int gerSenha(){ // gerar senha
    srand(time(0));
    
    return rand();
}
// ----------------------- Senhas Atendidas functions and returns -----------------------


senhasAtendidas* initAten(){
	senhasAtendidas *sAten = new senhasAtendidas;
	sAten->ini = NULL;
	sAten->fim = NULL;
	return sAten;
}


int isEmptyAten(Lista *lista) {
	return (lista->filaAtendida->ini == NULL);
}
// ----------------------- Lista functions and returns -----------------------

Lista* init(){
	return NULL;
}

int isEmpty(Lista* lista) {
	return (lista==NULL);
}

Lista* find(Lista* lista, int i) {
    Lista* aux;
	aux = lista;
	while (aux != NULL && aux->guiche != i) {
		aux = aux->prox;
	}	
	return aux;
}

int countGuiche(Lista* lista) {
    int i = 0;
    Lista* aux;
	aux = lista;
	while (aux != NULL) {
	    i+=1;
		aux = aux->prox;
	}	
	return i;
}

void print(Lista* lista){
    Lista* aux = lista;
	
	while(aux != NULL){
	    cout << "Guiche nº" << aux->guiche << endl;
	    noAtendido* senhaAtual = aux->filaAtendida->ini;
	    
	    while (senhaAtual != NULL) {
            cout << "Senha: " << senhaAtual->senha << endl;
            senhaAtual = senhaAtual->prox;
        }
	    aux = aux->prox;
	}
}

Lista* abrirGuiche(Lista* lista) {
    int i = 1; 
	Lista* novoGuiche = new Lista();
	novoGuiche->filaAtendida = initAten();
	
	while(find(lista, i) != NULL){
	    i+=1;
	}
	
	novoGuiche->guiche = i;
	novoGuiche->prox = lista;

	return novoGuiche;
}

void enfSenhaAtendida(Lista* lista, int id, int s){
    Lista* aux = lista;

	while(id != aux->guiche){
	   aux = aux->prox;
	}
	    
	cout << id << "ID == Guiche: " << aux->guiche << endl;
	   
	noAtendido *no = new noAtendido;
    no->senha = s;
    no->prox = NULL;
	
    if (isEmptyAten(aux)) {
        aux->filaAtendida->ini = no;
    }else{
        aux->filaAtendida->fim->prox = no;
    }
            	    
    aux->filaAtendida->fim = no;
}
// ----------------------- Opcoes -----------------------

void opcoes(senhasGeradas *sGer, Lista *listaAten){
    
    cout << "--------------------------------------";
    cout << endl << contSenhas(sGer) << " pessoas estao aguardando atendimento" << endl;
    cout << countGuiche(listaAten) << " guiches abertos" << endl;
    cout << "--------------------------------------";
    
    int opcao;
    int senha = gerSenha();
    int idGuiche;
    
    cout << "\nEscolha uma opcao:\n"       << endl
         << "0. Sair"                      << endl
         << "1. Gerar senha"               << endl
         << "2. Abrir guiche"              << endl
         << "3. Realizar atendimento"      << endl
         << "4. Listar senhas atendidas\n" << endl;
         
    cin >> opcao;
    
    switch(opcao){
        case 0:
            cout << "Sair" << endl;
            if(contSenhas(sGer) !=0)
            {
                cout << "Ainda ha clientes para serem atendidos!" << endl;
                opcoes(sGer, listaAten);
            }
            break;
        case 1:
            cout << "Gerar senha"  << endl;
            cout << "Senha " << senha << " gerada" << endl;
            enfSenhaGer(sGer, senha);
            opcoes(sGer, listaAten);
            break;
        case 2:
            cout << "Abrir guiche" << endl;
            
            listaAten = abrirGuiche(listaAten);
            
            opcoes(sGer, listaAten);
            break;
        case 3:
            cout << "Realizar atendimento" << endl;
            cout << "Digite o nº do guiche: ";
            cin >> idGuiche;
            
            if(find(listaAten, idGuiche) != NULL){
                enfSenhaAtendida(listaAten, idGuiche, senhaVez(sGer));
                desSenhaGer(sGer);
            }else{
                cout << endl << "Informe um guiche existente!" << endl;
            }
            
            opcoes(sGer, listaAten);
            break;
        case 4:
            cout << "Listar senhas atendidas" << endl;
            print(listaAten);
            
            opcoes(sGer, listaAten);
            break;
        default:
            cout << "!!! POR FAVOR, SELECIONE UMA OPCAO DE 0 A 4 !!!" << endl;
            opcoes(sGer, listaAten);
    }
}

int main()
{
    senhasGeradas *geradaInt;
    Lista *minhaLista;
    
    geradaInt = initGer();
	minhaLista = init();
	
	opcoes(geradaInt, minhaLista);

    return 0;
}