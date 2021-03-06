//Renan Carlos Loewenstein
//funciona no replit

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 6 //define a dimensão da matriz

typedef struct aresta{
	int origem;
	int destino;
	int value;
} Aresta;

typedef struct arestaLista{
	Aresta *aresta;
	struct arestaLista *next;
} ListEdge;

typedef struct{
	ListEdge *list_edge;
} Grafo;

typedef struct{
	int root[N];
	ListEdge *list_edge;
} Data;

Grafo *inicializarGrafo(){
	Grafo *grafo=malloc(sizeof(Grafo));
	grafo->list_edge=NULL;
	return grafo;
}

Data *inicailizarDados(){
  	Data *data=malloc(sizeof(Data));
	int n;

	for(n=0; n<N; n++){ 
		data->root[n]=-1;
  	}
	return data;
}

ListEdge *insertSortedEdge(ListEdge *list_edge, int origem, int destino, int value){
	ListEdge *aux, *ant=NULL;
	ListEdge *newElement=malloc(sizeof(ListEdge));

	newElement->aresta=malloc(sizeof(Aresta));
	newElement->aresta->origem=origem;
	newElement->aresta->destino=destino;
	newElement->aresta->value=value;

	newElement->next=NULL;
	aux=list_edge;

	while(aux!=NULL&&aux->aresta->value<=value) {
		ant=aux;
		aux=aux->next;
	}
	if(ant==NULL) {
		newElement->next=list_edge;
		list_edge=newElement;
	} else {
		newElement->next=ant->next;
		ant->next=newElement;
	}
	return list_edge;
}

ListEdge *insertEdge(ListEdge *list_edge, Aresta *aresta){
	ListEdge *aux,*newElement=malloc(sizeof(ListEdge));
	newElement->aresta=aresta;

	if(list_edge==NULL){
		list_edge=newElement;
	}
    else {
		aux=list_edge;
		while(aux->next!=NULL){ 
			aux=aux->next;
		}
		aux->next=newElement;
		newElement->next=NULL;		
	}
	return list_edge;
}

void printListEdge(ListEdge *head){
	ListEdge *aux=head;

	printf("Caminho ate agora:\n");
	while(aux!=NULL){
		printf("(%d, %d), ", aux->aresta->origem, aux->aresta->destino);
		aux= aux->next;
	}
	printf("\n\n");
}

void printData(Data *data) {
	int n;
	printf("indi->|");
	for(n=0; n<N; n++) {
		printf(" %d \t|", n);
	}
	printf("\n");
	printf("raiz->|");
	for ( n = 0; n < N; n++ ) {
		printf(" %d \t|", data->root[n] );
	}
	printf("\n\n");
}

void kruskal( ListEdge *list_edge, Data *data ) {
	int origin, destination;
	ListEdge *aux = list_edge;

	while(aux!=NULL) {
		printf("\n****** Estado atual ********\n");
		
		origin=aux->aresta->origem;
		destination=aux->aresta->destino;

		if(data->root[origin]>=0) {
			origin=data->root[origin];
		}
		if(data->root[destination]>=0) {
			destination=data->root[destination];
		}
		printf("    {   Visitando: Aresta (%d, %d) - %d\n\n", aux->aresta->origem, aux->aresta->destino, aux->aresta->value );

		if(origin!=destination) {
			if ( data->root[origin]<data->root[destination]) {
				data->root[origin]+=data->root[destination];
				data->root[destination]=origin;
			} else {
				data->root[destination]+=data->root[origin];
				data->root[origin]=destination;
			}
			data->list_edge=insertEdge(data->list_edge, aux->aresta);
		} 
		printData(data);
		printListEdge(data->list_edge);
		aux=aux->next;
	}
}

int main() {
    int i, j;
	int matriz[N][N] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
    };
        
    Grafo *grafo=inicializarGrafo();
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            if(matriz[i][j]!=0) {
                grafo->list_edge=insertSortedEdge(grafo->list_edge,i,j,matriz[i][j]);
            }
        }
    }
    Data *data=inicailizarDados();
	kruskal(grafo->list_edge, data);
	return 0;
}
