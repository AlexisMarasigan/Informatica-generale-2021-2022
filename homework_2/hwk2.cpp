#include <iostream>
#include <vector>
#include <string>
#include "graphs.cpp"
#include <algorithm>

namespace homework2
{
    /// Inserire il NOME della squadra!
    std::string getName()
    {
        std::string name = "Makima's"; // Aggiungere qui il nome
        return name;
    }

    /// Inserire i numeri di MATRICOLA dei componenti della squadra!
    std::vector<std::string> getIDs()
    {
        std::string matricola_1 = "1950540"; // Aggiungere il primo numero di matricola
        std::string matricola_2 = "1963619"; // Aggiungere il secondo numero di matricola
        std::vector<std::string> matricole{matricola_1, matricola_2};
        return matricole;
    }

    /**
     * @brief Esercizio 1. NON modificare l'intestazione.
     *
     * @param N numero di pecore moltiplicate da Alibraji Fogazzari
     * @return long int numero di volte che viene moltiplicato N
     * per raggiungere o superare 10'000.
     */
    long int sheeps(long int N)
    {
        // Inserire qui il codice della funzione
        long int prodotto = 1;
        long int multipli = 1;
        while (prodotto < 10000)
        {
            prodotto = N * multipli;
            multipli++;
        }
        multipli = prodotto / N;
        return multipli;
    }

    struct Node
    {
        std::pair<int, int> position;
        int steps;
    };

    int TargetBFS(Node start, Node Target)
    {
        int steps;
        std::vector<int>
            left_moves{-2, -1, 1, 2, -2, -1, 1, 2};
        std::vector<int>
            right_moves{-1, -2, -2, -1, 1, 2, 2, 1};
        std::vector<std::string> visited;
        std::queue<Node> coda;
        coda.push(start);
        while (!coda.empty())
        {
            Node testa = coda.front();
            Node next;
            coda.pop();
            if (testa.position.first == Target.position.first && testa.position.second == Target.position.second)
                steps = 0;
            for (int i = 0; i < 8; i++)
            {
                next.position.first == testa.position.first + left_moves.at(i);
                next.position.second == testa.position.second + right_moves.at(i);
                std::string check = std::to_string(next.position.first) + std::to_string(next.position.second);
                std::reverse(visited.begin(), visited.end());
                if (check == visited.at(0) && next.position.first >= 0 && next.position.second >= 0 && next.position.first <= 7 && next.position.second <= 7)
                {
                    next.steps++;
                    coda.push(next);
                    visited.push_back(check);
                }
            }

            steps == next.steps;
        }
        return steps;
    }

    /**
     * @brief Esercizio 2. NON modificare l'intestazione.
     *
     * @param source posizione di partenza del cavallo
     * @param dest posizione di arrivo del cavallo
     * @return int numero minimo di mosse necessarie al cavallo
     * per arrivare in dest partendo da source.
     */
    int knightMoves(std::pair<int, int> source, std::pair<int, int> dest)
    {
        // Inserire qui il codice della funzione
        int mosse = 0;

        Node start, Target;
        start.position = source;
        Target.position = dest;
        mosse = TargetBFS(start, Target);

        return mosse;
    }

    /**
     * @brief Esercizio 3. NON modificare l'intestazione.
     *
     * @param n numero di città
     * @param airports vettore con gli indici delle città in cui c'è già un aeroporto
     * @param flights coppie (i,j) per cui la compagnia aerea ha aperto/può aprire una tratta fra le città i,j
     * @param x città di partenza della tratta
     * @param y città di arrivo della tratta
     * @return int numero minimo di aeroporti da aprire per collegare x, y (-1 se impossibile)
     */
    int newAirports(int n, std::vector<int> airports, std::vector<std::pair<int, int>> flights, int x, int y)
    {
        // Inserire qui il codice della funzione
        int new_airports = -1;
        graphs::GenGraph cities(n);
        for (std::pair<int, int> i : flights)
        {
            graphs::Edge voli;
            voli.source = i.first;
            voli.dest = i.second;
            cities.addEdge(voli);
        }

        return new_airports;
    }
}