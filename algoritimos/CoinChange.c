#include <stdio.h>
#include <stdlib.h>


int main(){

 // atribuição de valores a variaveis
    int S = 0;
    int qntd_C = 0;
    printf("S: ");
    scanf("%d", &S);
    getchar();
    int * d = (int*)malloc(sizeof(int)*(S+1));
    printf("qntd_C: ");
    scanf("%d", &qntd_C);
    getchar();
    int * C = (int*)malloc(sizeof(int)*qntd_C);
    for (int i = 0, temp = 0; i < qntd_C ; i++)
    {
        printf("moeda %d: ", i);
        scanf("%d", &temp);
        getchar();
        C[i] = temp;
    }

    for (int i = 0; i <= S; i++)
    {
        d[i] = i;
    }
    int dif = 0;
    int soma = 0;
    for (int i = 0; i < qntd_C; i++)
    {
        for (int j = C[i]; j <= S; j++)
        {
            dif = j - C[i];
            soma = 1 + d[dif]; 
            if((d[j] > soma || d[j] == 0))
            {
                d[j] = soma;
            }
            
            
            printf(" dif: %d , j: %d , C[i]: %d\n", dif,j, C[i]);
        }   
    }
    printf("Qntd moedas: %d \n", d[S]);
    /**/
    for (int i = 0; i <= S; i++)
    {
        printf(" %d", d[i]);
    } 
    /**/

    



 // liberando espaço alocado
    free(C);
    free(d);

    
    return 0;
}