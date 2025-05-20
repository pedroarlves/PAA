#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAX_VERTICES 100000

// Estrutura para representar um grafo
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    Node** adj;
    int V;
} Graph;

// Criar um novo nó
Node* newNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

// Criar um grafo
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Adicionar aresta
void addEdge(Graph* graph, int src, int dest) {
    Node* node = newNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
    node = newNode(src);
    node->next = graph->adj[dest];
    graph->adj[dest] = node;
}

// Remover aresta
void removeEdge(Graph* graph, int u, int v) {
    Node** curr = &graph->adj[u];
    while (*curr) {
        if ((*curr)->dest == v) {
            Node* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }
    curr = &graph->adj[v];
    while (*curr) {
        if ((*curr)->dest == u) {
            Node* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }
}

// DFS para verificar conectividade
void DFS(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    for (Node* temp = graph->adj[v]; temp; temp = temp->next) {
        if (!visited[temp->dest])
            DFS(graph, temp->dest, visited);
    }
}

// Verifica se o grafo continua conectado sem a aresta (u, v)
bool isConnected(Graph* graph, int V, int u, int v) {
    bool* visited = (bool*)calloc(V, sizeof(bool));
    int start = 0;
    while (start < V && graph->adj[start] == NULL)
        start++;
    DFS(graph, start, visited);
    bool connected = true;
    for (int i = 0; i < V; i++) {
        if (graph->adj[i] && !visited[i]) {
            connected = false;
            break;
        }
    }
    free(visited);
    return connected;
}

// Método ingênuo para encontrar pontes
void naiveFindBridges(Graph* graph) {
    for (int u = 0; u < graph->V; u++) {
        for (Node* temp = graph->adj[u]; temp; temp = temp->next) {
            int v = temp->dest;
            removeEdge(graph, u, v);
            if (!isConnected(graph, graph->V, u, v))
                printf("Bridge found: %d - %d\n", u, v);
            addEdge(graph, u, v);
        }
    }
}

// Algoritmo de Tarjan para encontrar pontes
void tarjanDFS(Graph* graph, int u, bool visited[], int disc[], int low[], int parent, int* time) {
    visited[u] = true;
    disc[u] = low[u] = ++(*time);
    for (Node* temp = graph->adj[u]; temp; temp = temp->next) {
        int v = temp->dest;
        if (!visited[v]) {
            tarjanDFS(graph, v, visited, disc, low, u, time);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            if (low[v] > disc[u])
                printf("Bridge found: %d - %d\n", u, v);
        } else if (v != parent) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void tarjanFindBridges(Graph* graph) {
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    int* disc = (int*)calloc(graph->V, sizeof(int));
    int* low = (int*)calloc(graph->V, sizeof(int));
    int time = 0;
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i])
            tarjanDFS(graph, i, visited, disc, low, -1, &time);
    }
    free(visited);
    free(disc);
    free(low);
}

// Função principal para teste
typedef void (*BridgeFinder)(Graph*);

void benchmark(BridgeFinder method, Graph* graph, const char* methodName) {
    clock_t start = clock();
    method(graph);
    clock_t end = clock();
    printf("%s took %lf seconds\n", methodName, (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    int V = 100; // Exemplo com 100 vértices
    Graph* graph = createGraph(V);
    for (int i = 0; i < V - 1; i++)
        addEdge(graph, i, i + 1);
    addEdge(graph, 0, V - 1);
    benchmark(naiveFindBridges, graph, "Naive Method");
    benchmark(tarjanFindBridges, graph, "Tarjan's Method");
    return 0;
}
