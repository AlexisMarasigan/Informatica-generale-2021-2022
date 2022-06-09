#ifndef MOVE_H
#define MOVE_H

#include "board.h"

namespace move
{
    /// Tipo di azione permessa in Hex
    enum class ActionKind
    {
        ADD,
        SWAP,
        NOTHING
    };

    /**
     * @brief Classe che rappresenta le azioni elementari eseguibili su
     * una scacchiera di Hex.
     *
     */
    class Action
    {
    public:
        /// Tipo di azione
        ActionKind kind;
        /// Pezzo coinvolto nell'azione
        board::Piece piece;
        /// Posizione a cui si riferisce l'azione
        std::pair<int, int> position;

        /// Default constructor
        Action()
        {
            kind = ActionKind::NOTHING;
            piece = board::Piece::EMPTY;
            position = std::make_pair(0, 0);
        }

        /**
         * @brief Crea un'azione dati il tipo, il pezzo coinvolto e una posizione
         *
         * @param k tipo di azione
         * @param p pezzo coinvolto nell'azione (board::Piece)
         * @param pos posizione della scacchiera su cui agisce l'azione
         */
        Action(ActionKind k, board::Piece p, std::pair<int, int> pos)
        {
            kind = k;
            piece = p;
            position = pos;
        }

        Action &operator=(const Action &a)
        {
            kind = a.kind;
            piece = a.piece;
            position = a.position;
            return *this;
        }
    };

    constexpr bool operator==(const Action &a1, const Action &a2)
    {
        return ((a1.kind == a2.kind) && (a1.piece == a2.piece) && (a1.position == a2.position));
    }

    /// Mosse consentite a Hex: aggiungere una pedina, utilizzo della pie rule e resa
    enum class MoveKind
    {
        ADD,
        SWAP,
        RESIGN
    };

    /**
     * @brief Classe che rappresenta tutte le possibili mosse consentite
     * in una partita di Hex.
     *
     */
    class Move
    {
    public:
        MoveKind kind;
        Action action;

        /**
         * @brief Crea una mossa di tipo RESIGN
         *
         * @param k tipo della mossa (resa)
         */
        Move()
        {
            kind = MoveKind::RESIGN;
        }

        /**
         * @brief Crea una mossa di tipo ADD o SWAP (pie rule)
         *
         * @param k tipo della mossa
         * @param a azione corrispondente
         */
        Move(MoveKind k, Action a)
        {
            kind = k;
            action = a;
        }
    };

    constexpr bool operator==(const Move &m1, const Move &m2)
    {
        return ((m1.kind == m2.kind) && (m1.action == m2.action));
    }

}

#endif