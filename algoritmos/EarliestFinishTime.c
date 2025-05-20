#include <stdio.h>
#include <stdlib.h>

typedef struct job
{
    int inicio;
    int fim;
}Job;

Job new_Job(int inicio, int fim){
    Job  *temp = (Job*)malloc(sizeof(Job));
    if (temp)
    {
        temp->inicio = inicio;
        temp->fim    = fim;
    }
    return *temp; 
}
int main(){
    Job job = new_Job(5, 4);  
    printf("inicio: %d, fim: %d", job.inicio, job.fim);

    return 0;
}