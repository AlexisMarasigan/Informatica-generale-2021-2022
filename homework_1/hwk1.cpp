#include <iostream>
#include <vector>
#include <algorithm>
#include "graphs.h"

namespace homework
{

    /**
     * funzione che inverte gli archi in un grafo direzionato
     *
     * @param graph riferimento al grafo in input
     * @return graphs::Graph grafo con stessi vertici dell'input,ma archi con
     * direzione opposta
     */
    graphs::Graph invert_graph(graphs::Graph &graph)
    {
        graphs::Graph inv_graph(graph.getNumVertices()); // inizializzo un nuovo grafo
        for (int i = 0; i < graph.getNumVertices(); i++)
            for (int j : graph.getNeighbors(i))
            {
                inv_graph.addEdge(j, i); // per ogni vicino di un vertice nel grafo originale
            }                            // creo un arco dal vicino al vertice preso in considerazione
        return inv_graph;
    }

    /**
     * Funzione ricorsiva per la visita DFS, controlla se v è stato visitato, altrimenti lo visita
     *
     * @param graph riferimento al grafo in input
     * @param v vertice di partenza
     * @param visit_order ordine di visita dei vertici
     * @param visited  vettore di bool che segna se un vertice e' stato visitato o meno
     */
    void dfsRecur(graphs::Graph &graph, unsigned int v,
                  std::vector<int> &visit_order, std::vector<bool> &visited) // copia-incollata da graphs.cpp
    {
        if (!visited.at(v))
        {
            visited.at(v) = true;
            for (int x : graph.getNeighbors(v))
                if (!visited.at(x))
                    dfsRecur(graph, x, visit_order, visited);
            visit_order.push_back(v);
        }
    }

    /**
     * funzione che calcola i vertici raggiungibili a partire da un vertice scelto
     *
     * @param graph riferimento al grafo in input
     * @param v vertice di partenza
     * @param visited vettore di bool che segna se un vertice e' stato visitato o meno
     * @return std::vector<int> vettore dei vertici raggiungibili da v ordinati in post order
     */
    std::vector<int> explore(graphs::Graph &graph, unsigned int v, std::vector<bool> visited) // E'depthFirstSearchRec,ho solo tolto il vettore di bool
    {                                                                                         // che imposta a falso i vertici
        std::vector<int> visit_order;
        dfsRecur(graph, v, visit_order, visited);
        return visit_order;
    }

    /**
     * funzione che calcola i vertici di un grafo ordinati in post order crescente
     *
     * @param graph riferimento al grafo in input
     * @return std::vector<int> vettore contenente i vertici del grafo
     * ordinato in post order crescente
     */
    std::vector<int> post_order(graphs::Graph graph)
    {
        std::vector<bool> visited(graph.getNumVertices(), false);
        std::vector<int> result;
        for (int i = 0; i < graph.getNumVertices(); i++)
        {
            if (!visited.at(i))
            {
                std::vector<int> dfs_rec = explore(graph, i, visited);
                for (int j : dfs_rec)
                {
                    visited.at(j) = true;
                    result.push_back(j);
                }
            }
        }
        return result;
    }

    /**
     * Funzione che calcola le componenti fortemente connesse di un grafo.
     *
     * Si consideri, ad esempio, il grafo con vertici 0,1,2,3 e archi
     * (0,1), (1,2), (2,0), (1,3). Le sue componenti fortemente connesse sono
     * {0,1,2} e {3}. Quindi l'output sarà un vettore v tale che:
     * v.at(0) sia il vettore {0,1,2} (prima componente)
     * v.at(1) sia il vettore {3} (seconda componente)
     * L'ordine delle componenti e dei vertici non è rilevante.
     *
     * @param graph riferimento al grafo in input
     * @return std::vector<std::vector<int>> vettore contenente le componenti
     * fortemente connesse, ognuna espressa come un vettore di vertici.
     */
    std::vector<std::vector<int>> stronglyConnectedComponents(graphs::Graph &graph)
    {
        std::vector<std::vector<int>> scc;
        graphs::Graph inv_graph = invert_graph(graph); // inverto il grafo

        std::vector<int> inv_post = post_order(inv_graph); // ne ricavo il post order

        std::reverse(inv_post.begin(), inv_post.end()); // inverto l'ordine del post order

        std::vector<bool> visited(graph.getNumVertices(), false); // DFS_plus sul grafo originale
        for (int i : inv_post)
        {
            if (!visited.at(i))
            {
                std::vector<int> cc = explore(graph, i, visited);
                scc.push_back(cc);
                for (int j : cc)
                {
                    visited.at(j) = true;
                }
            }
        }
        return scc;
    }
}
