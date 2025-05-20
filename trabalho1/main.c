// chamada de bibliotecas
#include <stdio.h>  
#include <stdlib.h>

int numVert = 0;

typedef struct vertice
{
    int id;
    int grau;
    struct vertice *adjacentes;
}Vertice;


Vertice *newVertice(int n){
    Vertice *temp = (Vertice*)malloc(sizeof(Vertice));
    if (temp == NULL)
    {
        printf("ERRO AO ALOCAR MEMORIA\n");
    }
    else{
        temp->id = ++numVert;
        temp->grau = -1;
        temp->adjacentes = NULL;
        if (n>=0){
            temp->adjacentes = (Vertice*)malloc(sizeof(Vertice)*n);
        }
        if (temp->adjacentes != NULL)
        {
            temp->grau = n;
        }
    }
    

    return temp;
}

int main(){
    printf("INICIO\n");
    Vertice *verti = newVertice(5);
    
printf("FIM\n");
    getchar();
}