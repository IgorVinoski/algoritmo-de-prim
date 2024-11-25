#include <bits/stdc++.h>

using namespace std;
//foi o q eu usei.
struct Grafo {
    int numeroVertices;
    int **matriz;
};

bool inicializaGrafo(Grafo *g, int numeroVertices) {
    if (g == nullptr || numeroVertices < 1) return false;

    g->numeroVertices = numeroVertices;

    g->matriz = new int *[numeroVertices];
    for (int i = 0; i < numeroVertices; i++) {
        g->matriz[i] = new int[numeroVertices];
        for (int j = 0; j < numeroVertices; j++) {
            g->matriz[i][j] = INT_MAX; // Inicializa como aresta inexistente
        }
    }
    return true;
}

bool insereAresta(Grafo *g, int v1, int v2, int peso) {
    if (v1 < 0 || v2 < 0 || v1 >= g->numeroVertices || v2 >= g->numeroVertices || peso <= 0) return false;
    g->matriz[v1][v2] = peso;
    g->matriz[v2][v1] = peso;
    return true;
}

void liberaGrafo(Grafo *g) {
    for (int i = 0; i < g->numeroVertices; i++) {
        delete[] g->matriz[i];
    }
    delete[] g->matriz;
}

void MSTPrim(Grafo *g, int *pai) {
    int numeroVertices = g->numeroVertices;

    // Aloca memória para os vetores auxiliares
    int *peso = new int[numeroVertices];
    bool *naMST = new bool[numeroVertices];

    // Inicializa vetores
    for (int i = 0; i < numeroVertices; ++i) {
        pai[i] = -1;
        peso[i] = INT_MAX;
        naMST[i] = false;
    }

    pai[0] = 0;       // A raiz da MST tem como pai ela mesma
    peso[0] = 0;      // O peso para adicionar o vértice raiz é 0
    
    while (true) {
        int u = -1;
        int minPeso = INT_MAX;

        // Encontra o vértice de menor peso ainda não na MST
        for (int i = 0; i < numeroVertices; ++i) {
            if (!naMST[i] && peso[i] < minPeso) {
                u = i;
                minPeso = peso[i];
            }
        }

        if (u == -1) break;  // Não há mais vértices para processar

        naMST[u] = true; // Adiciona o vértice à MST

        // Atualiza os pesos dos vértices adjacentes
        for (int v = 0; v < numeroVertices; ++v) {
            if (g->matriz[u][v] != INT_MAX && !naMST[v] && g->matriz[u][v] < peso[v]) {
                pai[v] = u;
                peso[v] = g->matriz[u][v];
            }
        }
    }

    // Exibe as arestas da MST
    cout << "Arestas da MST:\n";
    for (int i = 1; i < numeroVertices; ++i) { // Começa do índice 1
        if (pai[i] != -1) {
            cout << pai[i] << " - " << i << " (Peso: " << g->matriz[i][pai[i]] << ")\n";
        }
    }

    // Libera memória alocada dinamicamente
    delete[] peso;
    delete[] naMST;
}

int main() {
    Grafo g;

    int numeroVertices = 5;
    inicializaGrafo(&g, numeroVertices);

    insereAresta(&g, 0, 1, 2);
    insereAresta(&g, 0, 3, 6);
    insereAresta(&g, 1, 2, 3);
    insereAresta(&g, 1, 3, 8);
    insereAresta(&g, 1, 4, 5);
    insereAresta(&g, 2, 4, 7);
    insereAresta(&g, 3, 4, 9);

    cout << "Executando o Algoritmo de Prim...\n";

    // Aloca dinamicamente o vetor de pais
    int *pai = new int[numeroVertices];
    MSTPrim(&g, pai);

    // Libera memória do vetor de pais
    delete[] pai;

    liberaGrafo(&g);
    return 0;
}
