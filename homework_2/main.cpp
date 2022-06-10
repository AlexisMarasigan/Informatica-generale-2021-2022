#include <iostream>
#include <vector>
#include <algorithm>
#include "hwk2.cpp"

int main()
{
    std::string name = homework2::getName();
    if (name.empty())
        std::cout << "Nome vuoto, selezionare un nome.\n";
    else
        std::cout << "Nome scelto per la squadra: " << name << '\n';
    std::vector<std::string> matricole = homework2::getIDs();
    long matricola_1 = std::stol(matricole.at(0));
    long matricola_2 = std::stol(matricole.at(1));
    long matricola_inf = 1500000, matricola_sup = 2100000;
    if ((matricola_1 < matricola_inf) || (matricola_1 > matricola_sup))
        std::cout << "Matricola 1 non valida.\n";
    else
        std::cout << "Matricola 1: " << matricola_1 << '\n';
    if ((matricola_2 < matricola_inf) || (matricola_2 > matricola_sup))
        std::cout << "Matricola 2 non valida.\n";
    else
        std::cout << "Matricola 2: " << matricola_2 << '\n';
    long int n_1 = 3210, multipli_1 = 4;
    long int sheeps = homework2::sheeps(n_1);
    std::cout << "Esercizio 1: risposta = " << sheeps;
    if (sheeps == multipli_1)
        std::cout << ", CORRETTA.\n";
    else
        std::cout << ", ERRATA (era " << multipli_1 << ").\n";
    std::pair<int, int> p_1 = std::make_pair(1, 1);
    std::pair<int, int> p_2 = std::make_pair(1, 2);
    int mosse_sol = 3;
    int moves = homework2::knightMoves(p_1, p_2);
    std::cout << "Esercizio 2: risposta = " << moves;
    if (moves == mosse_sol)
        std::cout << ", CORRETTA.\n";
    else
        std::cout << ", ERRATA (era " << mosse_sol << ").\n";
    int n_3 = 5;
    std::vector<int> airports{0, 1, 2, 3};
    std::vector<std::pair<int, int>> flights{std::make_pair(0, 1),
                                             std::make_pair(1, 2), std::make_pair(0, 3), std::make_pair(3, 4)};
    int c_1 = 0, c_2 = 4;
    int new_airports = homework2::newAirports(n_3, airports, flights, c_1, c_2);
    int nuovi_aeroporti = 1;
    std::cout << "Esercizio 3: risposta = " << new_airports;
    if (nuovi_aeroporti == new_airports)
        std::cout << ", CORRETTA.\n";
    else
        std::cout << ", ERRATA (era " << nuovi_aeroporti << ").\n";
    return 0;
}