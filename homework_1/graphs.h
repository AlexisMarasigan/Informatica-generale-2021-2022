#ifndef GRAPHS_H 
#define GRAPHS_H

#include <vector>

namespace graphs {
/**
 * Classe per implementare un grafo non pesato.
 * 
 */
class Graph{
private:
    /// Lista di adiacenza del grafo, adj_list.at(i) contiene i vicini del vertice i
    std::vector<std::vector<int> > adj_list;
    /// Numero di vertici del grafo
    int n_vertices;

public:
    /**
     * Costruttore di un oggetto Graph dato il numero di vertici.
     * 
     * @param n_vertices 
     */
    Graph(unsigned int n_vertices);

    /**
     * Funzione per aggiungere un arco al grafo
     * 
     * @param u vertice sorgente dell'arco
     * @param v vertice destinazione dell'arco
     * @param undirected false di default, indica se va aggiunto anche l'arco invertito
     */
    void addEdge(int u, int v, bool undirected=false);

    /**
     * Ottiene i vicini di un dato vertice.
     * 
     * @param v vertice fissato
     * @return std::vector<int> vettore dei vicini di v, ovvero vertici per cui
     * esiste un arco uscente da v e incidente in essi
     */
    std::vector<int> getNeighbors (int v) const;

    /**
     * Funzione che restituisce il numero di vertici del grafo.
     * 
     * @return int numero di vertici del grafo
     */
    int getNumVertices() const;
};

/**
 * Funzione che esegue una Breadth-First Search in tempo lineare.
 * 
 * @param graph riferimento al grafo da visitare
 * @param v intero corrispondente al vertice di partenza della visita
 * @return std::vector<int> vettore dei vertici visitati in ordine di BFS
 */
std::vector<int> breadthFirstSearch(Graph& graph, unsigned int v);

/**
 * Funzione che esegue una Depth-First Search ricorsiva in tempo lineare.
 * 
 * @param graph riferimento al grafo da visitare
 * @param v intero corrispondente al vertice di partenza della visita
 * @return std::vector<int> vettore dei vertici visitati in post-ordine di DFS
 */
std::vector<int> depthFirstSearchRec(Graph& graph, unsigned int v);

/**
 * Funzione che esegue una Depth-First Search in tempo lineare senza ricorsione.
 * 
 * @param graph riferimento al grafo da visitare
 * @param v intero corrispondente al vertice di partenza della visita
 * @return std::vector<int> vettore dei vertici visitati in pre-ordine di DFS
 */
std::vector<int> depthFirstSearch(Graph& graph, unsigned int v);

}

#endif