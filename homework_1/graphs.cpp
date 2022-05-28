#include <queue>
#include <stack>
#include "graphs.h"

graphs::Graph::Graph(unsigned int n)
{
    adj_list.resize(n);
    n_vertices = n;
}

void graphs::Graph::addEdge(int u, int v, bool undirected)
{
    adj_list.at(u).push_back(v);
    if (undirected)
        adj_list.at(v).push_back(u);
}

std::vector<int> graphs::Graph::getNeighbors(int v) const
{
    return adj_list.at(v);
}

int graphs::Graph::getNumVertices() const
{
    return n_vertices;
}

std::vector<int> graphs::breadthFirstSearch(graphs::Graph &graph, unsigned int v)
{
    std::vector<bool> visited(graph.getNumVertices(), false);
    std::vector<int> visit_order;
    std::queue<int> bfs_queue;
    bfs_queue.push(v);
    visited.at(v) = true;
    visit_order.push_back(v);
    while (!bfs_queue.empty())
    {
        int u = bfs_queue.front();
        bfs_queue.pop();
        for (int x : graph.getNeighbors(u))
            if (!visited.at(x))
            {
                // std::cout << x << std::endl;
                visited.at(x) = true;
                visit_order.push_back(x);
                bfs_queue.push(x);
            }
    }
    return visit_order;
}

// Funzione ricorsiva per la visita DFS, controlla se v è stato visitato, altrimenti lo visita
void dfsRecur(graphs::Graph &graph, unsigned int v,
              std::vector<int> &visit_order, std::vector<bool> &visited)
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

std::vector<int> graphs::depthFirstSearchRec(graphs::Graph &graph, unsigned int v)
{
    std::vector<int> visit_order;
    std::vector<bool> visited(graph.getNumVertices(), false); // vettore dei vertici visitati (true/false)
    dfsRecur(graph, v, visit_order, visited);
    return visit_order;
}

std::vector<int> graphs::depthFirstSearch(graphs::Graph &graph, unsigned int v)
{
    std::vector<int> visit_order;
    std::vector<bool> visited(graph.getNumVertices(), false); // vettore dei vertici visitati (true/false)
    std::stack<int> dfs_stack;
    dfs_stack.push(v);
    while (!dfs_stack.empty())
    {
        int u = dfs_stack.top();
        dfs_stack.pop();
        if (!visited.at(u))
        {
            visited.at(u) = true;
            visit_order.push_back(u);
            std::vector<int> neighbors = graph.getNeighbors(u);
            // Scanning the neighbors list in reverse order
            for (int i = neighbors.size() - 1; i >= 0; i--)
                dfs_stack.push(neighbors.at(i));
        }
    }
    return visit_order;
}