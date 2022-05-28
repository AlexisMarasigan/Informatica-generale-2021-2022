#include <iostream>
#include <vector>
#include <fstream>
#include "graphs.cpp"
#include "hwk1.cpp"

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        std::string file_name = argv[1];
        std::ifstream infile(file_name);
        unsigned int n_vertices;
        infile >> n_vertices;
        graphs::Graph graph(n_vertices);
        unsigned int m_edges;
        infile >> m_edges;
        int u, v;
        for (int i = 0; i < m_edges; i++)
        {
            infile >> u >> v;
            graph.addEdge(u, v);
        }
        std::vector<std::vector<int>> scc = homework::stronglyConnectedComponents(graph);
        for (auto i : scc)
        {
            for (auto j : i)
            {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }

        std::cout << scc.size() << std::endl;
    }
    return 0;
}