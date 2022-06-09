/**
 * @file main_test.cpp
 * @brief Test per il punteggio del progetto
 *
 */

#include <iostream>
#include <sstream>
#include <vector>
#include "board.h"
#include "move.h"
#include "game.h"
#include "player.h"
#include "game_ruler.h"
#include "test_players.h"

int getWins(gameRuler::HexGameRuler &hex_game_ruler, player::AbstractPlayer &p_1, player::AbstractPlayer &p_2, int seconds_per_move, int n_matches)
{
    int wins = 0, result;
    for (int i = 0; i < n_matches; i++)
    {
        result = hex_game_ruler.play(p_1, p_2, seconds_per_move);
        if (result == 1)
            wins += 1;
        result = hex_game_ruler.play(p_2, p_1, seconds_per_move);
        if (result == 2)
            wins += 1;
    }
    return wins;
}

int main()
{
    int score = 2;
    std::cout << "\nTEST 0: compiling, " << score << "pts\n";
    std::cout << "PASS\n----------\n";
    player::Player p;
    int score_name = 2;
    std::cout << "TEST 1: set name, " << score_name << "pts\n";
    std::string name = p.getName();
    if (!name.empty())
    {
        score += score_name;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    int score_ids = 2;
    std::cout << "TEST 2: set IDs, " << score_ids << "pts\n";
    std::string ids = p.getIDs();
    if (!ids.empty())
    {
        std::stringstream ids_ss(ids);
        std::string segment = " ";
        std::vector<std::string> seglist;
        while (std::getline(ids_ss, segment, ' '))
        {
            seglist.push_back(segment);
        }
        if ((seglist.empty()) || (seglist.size() != 2))
            std::cout << "FAIL\n----------\n";
        else
        {
            long int id_1 = std::stol(seglist.at(0));
            long int id_2 = std::stol(seglist.at(1));
            long int id_inf = 1500000, id_sup = 2100000;
            if ((id_1 < id_inf) || (id_1 > id_sup) || (id_2 < id_inf) || (id_2 > id_sup))
                std::cout << "FAIL\n----------\n";
            else
            {
                score += score_ids;
                std::cout << "PASS\n----------\n";
            }
        }
    }
    else
        std::cout << "FAIL\n----------\n";
    int seconds_per_move = 10;
    gameRuler::HexGameRuler hex_game_ruler(11);
    test_players::DumbRandomPlayer dr_p;
    int score_dumb_1 = 2;
    std::cout << "TEST 3: dumb random player - level 0, " << score_dumb_1 << "pts\n";
    std::cout << "Beating a dumb random player 60\% of the times\n";
    int points_threshold_0 = 60;
    int n_matches = 10;
    int score_per_match = 100 / (2 * n_matches);
    int wins = getWins(hex_game_ruler, p, dr_p, seconds_per_move, n_matches);
    int points = score_per_match * wins;
    if (points >= points_threshold_0)
    {
        score += score_dumb_1;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    int score_dumb_2 = 2;
    std::cout << "TEST 4: dumb random player - level 1, " << score_dumb_2 << "pts\n";
    std::cout << "Beating a dumb random player 80\% of the times\n";
    int points_threshold_1 = 80;
    if (points >= points_threshold_1)
    {
        score += score_dumb_2;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    test_players::RandomPlayer r_p;
    int score_rand_1 = 2;
    std::cout << "TEST 5: random player - level 2, " << score_rand_1 << "pts\n";
    std::cout << "Beating a random player 60\% of the times\n";
    int points_threshold_2 = 60;
    wins = getWins(hex_game_ruler, p, r_p, seconds_per_move, n_matches);
    points = score_per_match * wins;
    if (points >= points_threshold_2)
    {
        score += score_rand_1;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    int score_rand_2 = 3;
    std::cout << "TEST 6: random player - level 3, " << score_rand_2 << "pts\n";
    std::cout << "Beating a random player 80\% of the times\n";
    int points_threshold_3 = 80;
    if (points >= points_threshold_3)
    {
        score += score_rand_2;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    test_players::SmartRandomPlayer sr_p;
    int score_smart_1 = 3;
    std::cout << "TEST 7: smart random player - level 4, " << score_smart_1 << "pts\n";
    std::cout << "Beating a smart random player 60\% of the times\n";
    int points_threshold_4 = 60;
    wins = getWins(hex_game_ruler, p, sr_p, seconds_per_move, n_matches);
    points = score_per_match * wins;
    if (points >= points_threshold_4)
    {
        score += score_smart_1;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    int score_smart_2 = 3;
    std::cout << "TEST 8: smart random player - level 5, " << score_smart_2 << "pts\n";
    std::cout << "Beating a smart random player 75\% of the times\n";
    int points_threshold_5 = 75;
    if (points >= points_threshold_5)
    {
        score += score_smart_2;
        std::cout << "PASS\n----------\n";
    }
    else
        std::cout << "FAIL\n----------\n";
    std::cout << "TOTAL SCORE: " << score << "/21\n----------\n";
}