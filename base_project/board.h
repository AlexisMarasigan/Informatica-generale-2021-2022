#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdexcept>
#include <queue>

namespace board
{
    /// Classe per descrivere le possibili pedine (Rosso/Blu/No pedina)
    enum class Piece
    {
        RED_DISC,
        BLUE_DISC,
        EMPTY
    };

    class HexBoard
    {
    private:
        /// Dimensione della scacchiera di Hex (per esempio, 11)
        int size;
        /// Stato della scacchiera con i suoi pezzi
        std::vector<std::vector<Piece>> hex_board;

    public:
        /**
         * @brief Costruttore di un oggetto Hex Board data la dimensione n.
         * Costruisce una board nxn vuota.
         *
         * @param n dimensione della scacchiera di Hex (per esempio, 11)
         */
        HexBoard(int n)
        {
            size = n;
            for (int i = 0; i < n; i++)
            {
                std::vector<Piece> row_i(n, Piece::EMPTY);
                hex_board.push_back(row_i);
            }
        }

        /**
         * @brief Costruttore di una board data una matrice quadrata di pezzi
         *
         * @param h matrice quadrata di pezzi
         * @throws InvalidArgumentException se la matrice non è quadrata
         */
        HexBoard(std::vector<std::vector<Piece>> h)
        {
            size = h.size();
            for (std::vector<Piece> v_p : h)
                if ((v_p.empty()) || (v_p.size() != size))
                    throw std::invalid_argument("Cannot initialize a board with a non-square matrix of pieces.");
            hex_board = h;
        }

        /// Default constructor
        HexBoard()
        {
            size = 0;
        }

        /// Copy constructor
        HexBoard(const HexBoard &board)
        {
            size = board.getSize();
            for (int i = 0; i < size; i++)
            {
                std::vector<Piece> row_i;
                for (int j = 0; j < size; j++)
                    row_i.push_back(board.getPieceAtPos(std::make_pair(i, j)));
                hex_board.push_back(row_i);
            }
        }

        /**
         * @brief Restituisce la dimensione della scacchiera di Hex
         *
         * @return int dimensione della scacchiera di Hex (per esempio, 11)
         */
        int getSize() const { return size; }

        /**
         * @brief Controlla che una posizione (i,j) appartenga alla scacchiera.
         *
         * @param pos coppia di interi (i,j)
         * @return true se è una posizione ammissibile nell'attuale scacchera (0 <= i,j < size)
         * @return false altrimenti
         */
        bool isValidPos(std::pair<int, int> pos) const
        {
            return ((pos.first >= 0) && (pos.second >= 0) && (pos.first < size) && (pos.second < size));
        }

        /**
         * @brief Ritorna una visuale (copia) della board con i suoi pezzi
         *
         * @return std::vector<std::vector<Piece>> vettore che in posizione (i,j)
         * contiene il corrispondente pezzo sulla board di hex.
         */
        std::vector<std::vector<Piece>> getBoardView() const { return hex_board; }

        /**
         * @brief Restituisce il tipo di pezzo in una data posizione della scacchiera
         *
         * @param pos coppia di interi (i,j) che individua una posizione sulla scacchiera
         * @return Piece tipo di pezzo in posizione (i,j)
         * @throws InvalidArgumentException se la posizione non è valida per l'attuale scacchiera
         */
        Piece getPieceAtPos(std::pair<int, int> pos) const
        {
            if (!isValidPos(pos))
                throw std::invalid_argument("Invalid Coordinates for a Position.");
            return hex_board.at(pos.first).at(pos.second);
        }

        /**
         * @brief Ritorna tutte le posizioni della scacchiera in cui
         * è presente il pezzo p.
         *
         * @param p pezzo tramite cui filtrare le posizioni.
         * @return std::vector<std::pair<int, int>> vettore contenente tutte le
         * coppie (i,j) tali che la scacchiera contiene il pezzo p nella casella
         * di riga i e colonna j.
         */
        std::vector<std::pair<int, int>> getPosByPiece(Piece p) const
        {
            std::vector<std::pair<int, int>> positions;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                    if (hex_board.at(i).at(j) == p)
                    {
                        positions.push_back(std::make_pair(i, j));
                    }
            }
            return positions;
        }

        /**
         * @brief Funzione che aggiunge una nuova pedina alla scacchiera.
         *
         * @param p tipo di pezzo da aggiungere alla scacchiera
         * @param pos posizione (i,j) in cui aggiungere il pezzo
         * @throws InvalidArgumentException se la posizione non è valida per l'attuale scacchiera
         * oppure se la posizione è già occupata da un'altra pedina.
         */
        void addPiece(Piece p, std::pair<int, int> pos)
        {
            if (!isValidPos(pos))
                throw std::invalid_argument("Invalid Coordinates for a Position.");
            if (getPieceAtPos(pos) != Piece::EMPTY)
                throw std::invalid_argument("Trying to Add a Piece to an Occupied Position.");
            hex_board.at(pos.first).at(pos.second) = p;
        }

        /**
         * @brief Funzione che cambia il colore di una pedina della scacchiera,
         * utile per implementare la "pie rule".
         *
         * @param pos posizione (i,j) in cui cambiare il pezzo (nella posizione simmetrica
         * rispetto alla diagonale)
         * @throws InvalidArgumentException se la posizione non è valida per l'attuale scacchiera
         * oppure se la posizione NON è già occupata da un'altra pedina.
         */
        void swapPiece(std::pair<int, int> pos)
        {
            if (!isValidPos(pos))
                throw std::invalid_argument("Invalid Coordinates for a Position.");
            if (getPieceAtPos(pos) == Piece::EMPTY)
                throw std::invalid_argument("Trying to Swap a Piece in an Empty Position.");
            Piece p = getPieceAtPos(pos);
            if (p == Piece::RED_DISC)
            {
                hex_board.at(pos.first).at(pos.second) = Piece::EMPTY;
                hex_board.at(pos.second).at(pos.first) = Piece::BLUE_DISC;
            }
            else
            {
                hex_board.at(pos.first).at(pos.second) = Piece::EMPTY;
                hex_board.at(pos.second).at(pos.first) = Piece::RED_DISC;
            }
            return;
        }

        /**
         * @brief Ritorna la lista delle posizioni adiacenti a una posizione data
         *
         * @param pos (i,j) posizioni di riferimento
         * @return std::vector<std::pair<int,int>> contiene tutte le posizioni (h,k)
         * che sono adiacenti alla posizione pos=(i,j) nella scacchiera.
         * @throws InvalidArgumentException se la posizione non è valida per l'attuale scacchiera.
         */
        std::vector<std::pair<int, int>> getAdjacentPos(std::pair<int, int> pos) const
        {
            if (!isValidPos(pos))
                throw std::invalid_argument("Invalid Coordinates for a Position.");
            std::vector<std::pair<int, int>> candidate_pos;
            candidate_pos.push_back(std::make_pair(pos.first - 1, pos.second));
            candidate_pos.push_back(std::make_pair(pos.first + 1, pos.second));
            candidate_pos.push_back(std::make_pair(pos.first, pos.second - 1));
            candidate_pos.push_back(std::make_pair(pos.first, pos.second + 1));
            candidate_pos.push_back(std::make_pair(pos.first - 1, pos.second + 1));
            candidate_pos.push_back(std::make_pair(pos.first + 1, pos.second - 1));
            std::vector<std::pair<int, int>> adjacent_pos;
            for (std::pair<int, int> p : candidate_pos)
                if (isValidPos(p))
                    adjacent_pos.push_back(p);
            return adjacent_pos;
        }

        /**
         * @brief Funzione che verifica se un dato colore è in una
         * situazione vincente di connessione.
         *
         * @param color colore (1=rosso, 2=blue)
         * @return true se esiste un cammino di colore color fra i rispettivi lati
         * @return false altrimenti
         * @throws InvalidArgumentException se il colore è diverso da 1/2.

         */
        bool checkWin(int color) const
        {
            if ((color != 1) && (color != 2))
                throw std::invalid_argument("Invalid Color for Winning Check.");
            std::vector<std::vector<bool>> visited_cells;
            for (int i = 0; i < getSize(); i++)
            {
                std::vector<bool> visited_row_i(getSize(), false);
                visited_cells.push_back(visited_row_i);
            }
            if (color == 1)
            {
                std::queue<std::pair<int, int>> bfs_queue;
                for (int i = 0; i < getSize(); i++)
                    if (getPieceAtPos(std::make_pair(0, i)) == Piece::RED_DISC)
                    {
                        bfs_queue.push(std::make_pair(0, i));
                        visited_cells.at(0).at(i) = true;
                    }
                while (!bfs_queue.empty())
                {
                    std::pair<int, int> p = bfs_queue.front();
                    bfs_queue.pop();
                    std::vector<std::pair<int, int>> adj_p = getAdjacentPos(p);
                    for (std::pair<int, int> a_p : adj_p)
                        if ((getPieceAtPos(a_p) == Piece::RED_DISC) && (!visited_cells.at(a_p.first).at(a_p.second)))
                        {
                            bfs_queue.push(a_p);
                            visited_cells.at(a_p.first).at(a_p.second) = true;
                        }
                }
                for (int i = 0; i < getSize(); i++)
                    if (visited_cells.at(getSize() - 1).at(i))
                    {
                        return true;
                    }
                return false;
            }
            std::queue<std::pair<int, int>> bfs_queue;
            for (int i = 0; i < getSize(); i++)
                if (getPieceAtPos(std::make_pair(i, 0)) == Piece::BLUE_DISC)
                {
                    bfs_queue.push(std::make_pair(i, 0));
                    visited_cells.at(i).at(0) = true;
                }
            while (!bfs_queue.empty())
            {
                std::pair<int, int> p = bfs_queue.front();
                bfs_queue.pop();
                std::vector<std::pair<int, int>> adj_p = getAdjacentPos(p);
                for (std::pair<int, int> a_p : adj_p)
                    if ((getPieceAtPos(a_p) == Piece::BLUE_DISC) && (!visited_cells.at(a_p.first).at(a_p.second)))
                    {
                        bfs_queue.push(a_p);
                        visited_cells.at(a_p.first).at(a_p.second) = true;
                    }
            }
            for (int i = 0; i < getSize(); i++)
                if (visited_cells.at(i).at(getSize() - 1))
                {
                    return true;
                }
            return false;
        }
    };

    bool operator==(const HexBoard &b1, const HexBoard &b2)
    {
        if (b1.getSize() != b2.getSize())
            return false;
        int size = b1.getSize();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (b1.getPieceAtPos(std::make_pair(i, j)) != b2.getPieceAtPos(std::make_pair(i, j)))
                    return false;
        return true;
    }
}

#endif