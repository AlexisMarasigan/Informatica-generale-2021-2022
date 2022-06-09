#ifndef GAME_RULER_H
#define GAME_RULER_H

#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
#include <future>
#include "board.h"
#include "move.h"
#include "game.h"
#include "player.h"

namespace gameRuler
{
    /// Function that gets a move chosen by a player under the current situation
    void getMoveFromPlayer(player::AbstractPlayer &p, game::Situation s, move::Move &m)
    {
        m = p.getMoveFromSit(s);
    }

    /**
     * @brief Hex GameRuler, utilizzato per giocare una o più
     * partite a Hex.
     *
     */
    class HexGameRuler
    {
    private:
        /// Configurazione di gioco corrente
        game::Situation current_situation;

    public:
        /**
         * @brief Costruttore di un Hex GameRuler data
         * la dimensione della scacchiera per Hex. Inizializza
         * la situazione di gioco alla configurazione iniziale
         * del gioco Hex.
         *
         * @param n dimensione della scacchiera di Hex (nxn).
         */
        HexGameRuler(int n)
        {
            board::HexBoard hex_board(n);
            game::Situation situation(hex_board, 1);
            current_situation = situation;
        }

        /// Default constructor
        HexGameRuler() = default;

        /// Reimposta la configurazione iniziale di Hex
        void setStart()
        {
            board::HexBoard hex_board(current_situation.getBoardView().size());
            game::Situation situation(hex_board, 1);
            current_situation = situation;
        }

        /**
         * @brief Gioca una partita a Hex con i giocatori correnti
         *
         * @param player_1 giocatore 1
         * @param player_2 giocatore 2
         * @param waiting_sec numero di secondi a disposizione per una mossa
         * @return int indice del giocatore che ha vinto, dove
         * l'indice è riferito all'indice nell'oggetto gameRuler.
         */
        int play(player::AbstractPlayer &player_1, player::AbstractPlayer &player_2, int waiting_sec)
        {
            setStart();
            int result = 1;
            while (current_situation.turn > 0)
            {
                move::Move next_move;
                if (current_situation.turn == 1)
                {
                    std::thread control_thread(getMoveFromPlayer, std::ref(player_1), current_situation, std::ref(next_move));
                    auto future = std::async(std::launch::async, &std::thread::join, &control_thread);
                    if (future.wait_for(std::chrono::seconds(waiting_sec)) == std::future_status::timeout)
                    {
                        std::cout << "Tempo esaurito per il giocatore " << player_1.getName() << '\n';
                        return 2;
                    }
                    if (!current_situation.isValid(next_move))
                    {
                        return 2;
                    }
                    current_situation = current_situation.next(next_move);
                }
                else
                {
                    std::thread control_thread(getMoveFromPlayer, std::ref(player_2), current_situation, std::ref(next_move));
                    auto future = std::async(std::launch::async, &std::thread::join, &control_thread);
                    if (future.wait_for(std::chrono::seconds(waiting_sec)) == std::future_status::timeout)
                    {
                        std::cout << "Tempo esaurito per il giocatore " << player_2.getName() << '\n';
                        return 1;
                    }
                    if (!current_situation.isValid(next_move))
                    {
                        return 1;
                    }
                    current_situation = current_situation.next(next_move);
                }
            }
            result = -current_situation.turn;
            return result;
        }
    };

}

#endif