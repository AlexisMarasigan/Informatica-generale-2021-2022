#ifndef TEST_PLAYERS_H 
#define TEST_PLAYERS_H

#include<vector>
#include<algorithm>
#include<random>
#include "move.h"
#include "game.h"
#include "player.h"

namespace test_players {
    /**
     * @brief Giocatore che sceglie una mossa a caso fra
     * quelle disponibili, eventualmente anche la mossa
     * di tipo RESIGN.
     * 
     */
    class DumbRandomPlayer : public player::AbstractPlayer {
        public:
        std::string getName() {
            return "Dumb Random Player";
        }

        std::string getIDs() {
            return "noID";
        }

        move::Move getMoveFromSit(game::Situation situation) {
            std::vector<move::Move> valid_moves = situation.validMoves();
            std::shuffle(valid_moves.begin(), valid_moves.end(), std::default_random_engine(19));
            return valid_moves.at(0);
        }
    };

    /**
     * @brief Giocatore che sceglie una mossa a caso fra
     * quelle disponibili, evitando sempre la mossa
     * di tipo RESIGN.
     * 
     */
    class RandomPlayer : public player::AbstractPlayer {
        public:
        std::string getName() {
            return "Random Player";
        }

        move::Move getMoveFromSit(game::Situation situation) {
            std::vector<move::Move> valid_moves = situation.validMoves();
            std::shuffle(valid_moves.begin(), valid_moves.end(), std::default_random_engine(19));
            move::Move move = valid_moves.at(0);
            if (move.kind == move::MoveKind::RESIGN)
                return valid_moves.at(1);
            return move;
        }
    };

    /**
     * @brief Giocatore che sceglie una mossa fra quelle disponibili
     * nel seguente modo:
     * - se esiste una mossa che lo porta direttamente alla vittoria, la sceglie
     * - altrimenti, sceglie una mossa a caso evitando sempre la mossa RESIGN.
     * 
     */
    class SmartRandomPlayer : public player::AbstractPlayer {
        public:
        std::string getName() {
            return "Smart Random Player";
        }

        move::Move getMoveFromSit(game::Situation situation) {
            std::vector<move::Move> valid_moves = situation.validMoves();
            int current_turn = situation.turn;
            for (move::Move& m : valid_moves) {
                game::Situation next_sit = situation.next(m);
                if (next_sit.turn == -current_turn)
                    return m;
            }
            std::shuffle(valid_moves.begin(), valid_moves.end(), std::default_random_engine(19));
            move::Move move = valid_moves.at(0);
            if (move.kind == move::MoveKind::RESIGN)
                return valid_moves.at(1);
            return move;
        }
    };
}

#endif