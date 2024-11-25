#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Aresta {
    int destino, peso;
};

struct Grafo {
    int numeroVertices;
    vector<vector<Aresta>> listaAdj; // Lista de adjacência
};

// Inicializa um grafo com um dado número de vértices
bool inicializaGrafo(Grafo &g, int numeroVertices) {
    if (numeroVertices < 1) return false;
    g.numeroVertices = numeroVertices;
    g.listaAdj.resize(numeroVertices);
    return true;
}

// Insere uma aresta entre os vértices v1 e v2 com peso w
bool insereAresta(Grafo &g, int v1, int v2, int peso) {
    if (v1 < 0 || v2 < 0 || v1 >= g.numeroVertices || v2 >= g.numeroVertices) return false;
    g.listaAdj[v1].push_back({v2, peso});
    g.listaAdj[v2].push_back({v1, peso}); // Grafo não-direcionado
    return true;
}

// Exibe a lista de adjacência do grafo
void exibeGrafo(const Grafo &g) {
    for (int i = 0; i < g.numeroVertices; i++) {
        cout << i << ": ";
        for (const auto &aresta : g.listaAdj[i]) {
            cout << "(" << aresta.destino << ", " << aresta.peso << ") ";
        }
        cout << endl;
    }
}

// Implementação do algoritmo de Prim para calcular a MST
void primMST(const Grafo &g, vector<int> &pa) {
    vector<int> preco(g.numeroVertices, INT_MAX); 
    vector<bool> inTree(g.numeroVertices, false); 
    pa.assign(g.numeroVertices, -1);              
    preco[0] = 0;                                 
    pa[0] = 0;                                    

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0}); // (peso, vértice)

    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();

        if (inTree[v]) continue;
        inTree[v] = true;

        for (const auto &aresta : g.listaAdj[v]) {
            int u = aresta.destino;
            int peso = aresta.peso;

            if (!inTree[u] && peso < preco[u]) {
                preco[u] = peso;
                pa[u] = v;
                pq.push({peso, u});
            }
        }
    }
}

// Exibe a MST
void exibeMST(const vector<int> &pa) {
    cout << "Arestas da MST:\n";
    for (int v = 1; v < pa.size(); v++) {
        if (pa[v] != -1) { // Excluir vértices não conectados
            cout << pa[v] << " - " << v << endl;
        }
    }
}

int main() {
    Grafo g;
    inicializaGrafo(g, 6);

    // Inserção de arestas com pesos
    insereAresta(g, 0, 1, 2);
    insereAresta(g, 0, 3, 6);
    insereAresta(g, 1, 2, 3);
    insereAresta(g, 1, 3, 8);
    insereAresta(g, 1, 4, 5);
    insereAresta(g, 2, 4, 7);
    insereAresta(g, 3, 4, 9);

    cout << "Grafo representado como lista de adjacência:\n";
    exibeGrafo(g);

    vector<int> pa;
    primMST(g, pa);

    cout << "\nResultado do algoritmo de Prim:\n";
    exibeMST(pa);

    return 0;
}
