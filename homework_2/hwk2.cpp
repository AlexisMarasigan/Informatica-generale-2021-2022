#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include "graphs.cpp"

namespace homework2 {
    /// Inserire il NOME della squadra!
    std::string getName() {
        std::string name = "AC Milan";  // Aggiungere qui il nome
        return name;
    }

    /// Inserire i numeri di MATRICOLA dei componenti della squadra!
    std::vector<std::string> getIDs() {
        std::string matricola_1 = "1607862";  // Aggiungere il primo numero di matricola
        std::string matricola_2 = "1607862";  // Aggiungere il secondo numero di matricola
        std::vector<std::string> matricole{matricola_1, matricola_2};
        return matricole;
    }

    /**
     * @brief Esercizio 1. NON modificare l'intestazione.
     * 
     * @param N numero di pecore moltiplicate da Stefano Pioli
     * @return long int numero di volte che viene moltiplicato N
     * per superare 10'000.
     */
    long int sheeps(long int N) {
        // Inserire qui il codice della funzione
        long int multipli = 1;
        return multipli + 9999/N;
    }

    int isValidPos(int x, int y) {
        return ((x>=0) && (x<=7) && (y>=0) && (y<=7));
    }

    std::vector<std::pair<int,int>> adjacentPos(std::pair<int,int> pos) {
        std::vector<std::pair<int,int>> adj_pos;
        std::vector<int> short_side{-1, 1};
        std::vector<int> long_side{-2, 2};
        for (int t_s : short_side)
            for (int t_l: long_side) {
                if (isValidPos(pos.first + t_s, pos.second + t_l))
                    adj_pos.push_back(std::make_pair(pos.first + t_s, pos.second + t_l));
                if (isValidPos(pos.first + t_l, pos.second + t_s))
                    adj_pos.push_back(std::make_pair(pos.first + t_l, pos.second + t_s));
            }
        return adj_pos;
    }

    /**
     * @brief Esercizio 2. NON modificare l'intestazione.
     * 
     * @param source posizione di partenza del cavallo
     * @param dest posizione di arrivo del cavallo
     * @return int numero minimo di mosse necessarie al cavallo
     * per arrivare in dest partendo da source.
     */
    int knightMoves(std::pair<int,int> source, std::pair<int,int> dest) {
        // Inserire qui il codice della funzione
        int mosse = 0;
        if (source==dest)
            return mosse;
        std::vector<std::vector<int>> distances;
        for (int i=0; i<8; i++) {
            std::vector<int> row_i(8, 100);
            distances.push_back(row_i);
        }
        std::queue<std::pair<int,int>> bfs_queue;
        bfs_queue.push(source);
        distances.at(source.first).at(source.second) = 0;
        while (!bfs_queue.empty()) {
            std::pair<int,int> v = bfs_queue.front();
            bfs_queue.pop();
            std::vector<std::pair<int,int>> adj_v = adjacentPos(v);
            for (std::pair<int,int>& u : adj_v)
                if (distances.at(u.first).at(u.second)==100) {
                    distances.at(u.first).at(u.second) = distances.at(v.first).at(v.second) + 1;
                    bfs_queue.push(u);
                    if (u==dest) 
                        return distances.at(dest.first).at(dest.second);
                }
        }
        return distances.at(dest.first).at(dest.second);
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
    int newAirports(int n, std::vector<int> airports, std::vector<std::pair<int,int>> flights, int x, int y) {
        // Inserire qui il codice della funzione
        int new_airports = -1;
        int starting_airport_cost = 0;
        graphs::GenGraph italy(n);
        std::vector<bool> existing_airports(n, false);
        for (int a : airports)
            existing_airports.at(a) = true;
        if (!existing_airports.at(x))
            starting_airport_cost = 1;
        for (std::pair<int,int> f : flights) {
            double weight_s = 0, weight_d = 0;
            if (!existing_airports.at(f.second))
                weight_d = 1;
            if (!existing_airports.at(f.first))
                weight_s = 1;
            graphs::Edge e1{f.first, f.second, weight_d, ""};
            graphs::Edge e2{f.second, f.first, weight_s, ""};
            italy.addEdge(e1);
            italy.addEdge(e2);
        }
        std::vector<double> distances = graphs::shortestPaths(italy, x);
        if (distances.at(y) > n)
            return new_airports;
        return distances.at(y) + starting_airport_cost;
    }

}