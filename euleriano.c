#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_FILA  100

#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct aresta{
	int nome;
	struct aresta *prox;
}Aresta;

typedef struct vert{
	int nome;
	int cor;
	Aresta *prim;
}Vertice;



void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calcumaTamanho(Vertice G[], int ordem);
void percorreGrafo(Vertice G[], int vInicial, int ordem);
int  verificaEuleriano(Vertice G[], int ordem);
int verificaConexo(Vertice G[], int ordem);

//inicio do codigo da fila
typedef struct queue{
    int vector[MAX_FILA];
    int front;
    int back;
    int tam;
}Queue;

void initializeEmpty(Queue *f);
int isEmpty(Queue f);
void enqueue(Queue *f, int elem);
int dequeue(Queue *f);

void initializeEmpty(Queue *Q){
    Q->front = Q->back= 0;
}
int isEmpty(Queue Q){
    return Q.back == Q.front;
}

//adicionar elemento a fila
void enqueue(Queue *Q, int elem){ 
     Q->vector[Q->back] = elem;
     Q->back += 1;
     if(Q->back == MAX_FILA) {
        Q->back = 0;
     }
}

//retirar primeiro elemento da fila
int dequeue(Queue *Q){
	int back;
	if(Q->front == Q->back) {
       exit(1);
    }
    back = Q->vector[Q->front];
    Q->front += 1;
    if(Q->front == MAX_FILA) {
       Q->front = 0;
    }
    return back;              
 }

//fim do codigo da fila
 
void criaGrafo(Vertice **G, int ordem){
	int i;
	*G= (Vertice*) malloc(sizeof(Vertice)*ordem);
	
	for(i=0; i<ordem; i++){
		(*G)[i].nome= i;
		(*G)[i].cor= NONE;
		(*G)[i].prim= NULL;
	}
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2){
	if (v1<0 || v1 >= ordem)
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	Aresta *A1= (Aresta *) malloc(sizeof(Aresta));
	A1->nome= v2;
	A1->prox= G[v1].prim;
	G[v1].prim= A1;

	Aresta *A2= (Aresta *) malloc(sizeof(Aresta));
	A2->nome= v1;
	A2->prox= G[v2].prim;
	G[v2].prim= A2;
}


int  calcumaTamanho(Vertice G[], int ordem){
	int i;
	int totalArestas=0;
	
	for (i=0; i<ordem; i++){
		int j;
		Aresta *aux= G[i].prim;
		for(j=0; aux != NULL; aux= aux->prox, j++);
		totalArestas += j;	
	}
	return totalArestas/2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem){
	int i;

	for (i=0; i<ordem; i++){
		printf("\nV%d: ", i);
		Aresta *aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox)
			printf("%3d", aux->nome);
	}
	printf("\n\n");
}

//verifica se grafo é conexo utilizando as cores(preenchidas apos usar percorre grafo)
int verificaConexo(Vertice G[], int ordem){
	int i;  
	for (i=0; i<ordem; i++){
		Aresta *aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox){
	    	printf("G[%d] cor %3d i = %d\n", aux->nome, G[i].cor,i);	    	
		//caso a cor do vertice seja branco ele nao é conexo
		if((G[i].cor == 0)||(G[i].cor == -1)){
	    	   printf("\nGrafo nao conexo\n");
	    	   return 0;
			}
		}
	}
	//caso exista algum vertice que nao seja conexo(cor branco)
	printf("\nGrafo conexo\n");	
    return 1;
}

//percorre o grafo verificando a conexidade de cada vertice e atribuindo um valor para a cor de cada vertice(dependendo se é conexo ou não)
void percorreGrafo(Vertice G[], int vInicial, int ordem){			
	int i,j, u;					
	Queue *q = (Queue*) malloc(sizeof(Queue));	
	q->front = 0;
	//q->front = null;	
	q->back = 0;
	//q->back = null;
	u = vInicial;
	Aresta *aux= G[u].prim;
	//for para colorir todos os vertices de branco    	
	for (i=0; i<ordem; i++){
		Aresta *aux2= G[i].prim;
		for( ; aux2 != NULL; aux2= aux2->prox){
		    G[i].cor = BRANCO;
	     	}
	}  
    G[u].cor = CINZA;
    enqueue(q, G[u].nome);
    while(isEmpty(*q)!=1){
        u = dequeue(q);
	   	for(j=0; aux != NULL; aux= aux->prox, j++){
    	    if (G[aux->nome].cor == BRANCO) {
    	        G[u].cor = CINZA;
		    	enqueue(q, aux->nome);
	    	}
	    }
	    aux= G[u].prim;	        
        G[u].cor = PRETO;
    }       	        
}



int verificaGrauPar(Vertice G[], int ordem){
	int i;
	int verticeGrau[ordem];	
	for (i=0; i<ordem; i++){
		verticeGrau[i]=0;		
		printf("\nV%d: ", i);
		Aresta *aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox){
				verticeGrau[i]+=1;			
				printf("%3d", aux->nome);
		}
	}
	printf("\n\n");

		
	for (i=0; i<ordem; i++){
	
	printf("%3d", verticeGrau[i]);
	}return 0;

}

int verificaEuleriano(Vertice G[], int ordem){
	if( verificaConexo(G, ordem))//and verificagraupar
		
		printf("\n o é euleriano \n" );
	else
		printf("\n nao é euleriano \n" );


}

int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG= 10;
	
	criaGrafo(&G, ordemG);
	acrescentaAresta(G,ordemG,1,6);
	acrescentaAresta(G,ordemG,3,4);
	acrescentaAresta(G,ordemG,4,2);
	acrescentaAresta(G,ordemG,5,4);
	acrescentaAresta(G,ordemG,2,3);
	acrescentaAresta(G,ordemG,3,7);
	
	
	
	printf("\nTamanho: %d\n",calcumaTamanho(G, ordemG));

	imprimeGrafo(G, ordemG);
	
 	verificaGrauPar(G, ordemG);   	
	percorreGrafo(G, 2,ordemG);
	

	//if( verificaConexo(G, ordemG))
	//	printf("\n o é euleriano \n" );
	//else
	//	printf("\n nao é euleriano \n" );
    	// verificaConexo(G, ordemG);
	return 0;
}
