#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100005  // Limite máximo de vértices

int tin[MAX_NODES], low[MAX_NODES]; // Tempo de descoberta e menor tempo acessível
bool visited[MAX_NODES]; 
int timer = 0; // Contador de tempo
int **adj; // Lista de adjacências
int *adj_size; // Tamanho de cada lista de adjacências

// Função DFS para encontrar pontes
void dfs(int v, int parent) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    
    for (int i = 0; i < adj_size[v]; i++) {
        int to = adj[v][i];
        if (to == parent) continue; // Ignora aresta para o pai
        
        if (visited[to]) {
            low[v] = (low[v] < tin[to]) ? low[v] : tin[to];
        } else {
            dfs(to, v);
            low[v] = (low[v] < low[to]) ? low[v] : low[to];

            if (low[to] > tin[v]) {
                printf("Ponte encontrada: (%d, %d)\n", v, to);
            }
        }
    }
}

// Função para encontrar todas as pontes no grafo
void find_bridges(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        tin[i] = -1;
        low[i] = -1;
    }
    
    timer = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
}

// Função para adicionar uma aresta ao grafo
void add_edge(int u, int v) {
    adj[u] = realloc(adj[u], (adj_size[u] + 1) * sizeof(int));
    adj[v] = realloc(adj[v], (adj_size[v] + 1) * sizeof(int));

    adj[u][adj_size[u]++] = v;
    adj[v][adj_size[v]++] = u;
}

// Função principal
int main() {
    int n, m; // Número de vértices e arestas
    printf("Digite o número de vértices e arestas: ");
    scanf("%d %d", &n, &m);

    // Alocar memória para a lista de adjacências
    adj = (int **)malloc(n * sizeof(int *));
    adj_size = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
        adj_size[i] = 0;
    }

    printf("Digite as %d arestas (formato: u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    printf("Procurando pontes...\n");
    find_bridges(n);

    // Liberar memória
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adj_size);

    return 0;
}
