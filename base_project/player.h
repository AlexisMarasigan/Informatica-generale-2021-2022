#ifndef PLAYER_H 
#define PLAYER_H

#include<string>
#include "board.h"
#include "move.h"
#include "game.h"

/** In questo namespace potete aggiungere tutte le classi e le funzioni di 
 *  cui avete bisogno, ma non potete in alcun modo modificare 
 *  le funzioni già esistenti.
 */
namespace player {
    // NON TOCCARE. Classe astratta, utile per i test.
    class AbstractPlayer {
    public:
        virtual std::string getName() = 0;
        virtual std::string getIDs() {
            return "";
        }
        virtual move::Move getMoveFromSit(game::Situation situation) = 0;
    };

    /**
     * CLASSE DA COMPLETARE PER IL PROGETTO.
     * Classe che implementa il giocatore di Hex.
     * Il giocatore è caratterizzato da un nome, dai
     * numeri di matricola degli studenti che lo hanno
     * programmato e dalla funzione getMoveFromSit(Situation sit)
     * che riceve una situazione di gioco e ritorna in output
     * la mossa scelta dal giocatore in tale situazione.
     */
    class Player : public AbstractPlayer {
        public:
        /**
         * @brief Restituisce  il nome della squadra
         * INSERIRE IL NOME!
         * @return std::string nome della squadra
         */
        std::string getName() {
            std::string player_name="";
            return player_name;
        }

        /**
         * @brief restituisce le matricole dei due componenti della squadra
         * INSERIRE LE MATRICOLE!
         * @return std::string matricole separate da uno spazio
         */
        std::string getIDs() {
            std::string matricola_1="";
            std::string matricola_2="";
            return matricola_1 + " " + matricola_2;
        }

        /**
         * FUNZIONE DA IMPLEMENTARE PER IL PROGETTO. NON cambiare
         * l'intestazione, ma scrivere solo nel corpo della funzione.
         * 
         * Questa funzione riceve in input una configurazione o situazione
         * di gioco e restituisce in output la mossa scelta dal giocatore.
         * 
         * @param situation configurazione o situazione di gioco
         * @return move::Move mossa scelta dal giocatore
         */
         move::Move getMoveFromSit(game::Situation situation)
        {
            move::Move m;
            if (situation.pieRule())
                m.kind = move::MoveKind::SWAP;
            else
            {
                m = getMoveFromSit(situation.next(m));
            }
            return m;
        }
    };

}

#endif
