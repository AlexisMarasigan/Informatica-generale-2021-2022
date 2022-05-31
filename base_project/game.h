#ifndef GAME_H 
#define GAME_H

#include<string>
#include<vector>
#include<stdexcept>
#include "board.h"
#include "move.h"

namespace game {
    /// Classe che descrive una configurazione di gioco
    class Situation {
        private:
        /// Board corrispondente alla configurazione
        board::HexBoard board;

        public:
        /// Turno di gioco (1=rosso, 2=blu, -1=vittoria rosso, -2=vittoria blu)
        /// Usare situation.turn per accedere a questo campo
        int turn;

        /**
         * @brief Costruttore di un oggetto Situation
         * 
         * Dati un oggetto b di tipo board::HexBoard e un turno t (int)
         * game::Situation situation(b, t);
         * crea un oggetto di tipo Situation chiamato situation
         * 
         * @param b board attuale del gioco
         * @param t turno corrente
         */
        Situation(board::HexBoard b, int t) {
            board=board::HexBoard(b);
            turn=t;
        }  

        /**
         * @brief Restituisce il tipo di pezzo in una data posizione della scacchiera
         * 
         * @param pos coppia di interi (i,j) che individua una posizione sulla scacchiera
         * @return board::Piece tipo di pezzo in posizione (i,j)
         * @throws InvalidArgumentException se la posizione non è valida per l'attuale scacchiera
         * 
         * board::Piece p = situation.getPieceAtPos(std::make_pair(0,0))
         * restituisce il pezzo in posizione (0,0), riga 0 e colonna 0
         */
        board::Piece getPieceAtPos(std::pair<int,int> pos) const {
            return board.getPieceAtPos(pos);
        }

        /**
         * @brief Ritorna una visuale della board con i suoi pezzi
         * 
         * @return std::vector<std::vector<board::Piece>> vettore che in posizione (i,j)
         * contiene il corrispondente pezzo sulla board di hex. Si noti che si può
         * usare un costruttore di board per ottenere un oggetto di tipo HexBoard.
         * 
         * std::vector<std::vector<board::Piece>> board_view = situation.getBoardView();
         * board::HexBoard board(board_view);
         */
        std::vector<std::vector<board::Piece>> getBoardView() const {return board.getBoardView();}

        /**
         * @brief Verifica se si può usare la pie rule
         * 
         * @return true se la piè rule è utilizzabile al turno corrente
         * @return false altrimenti
         * 
         * Esempio di utilizzo:
         * if (situation.pieRule()) ...
         */
        bool pieRule() const {
            if (turn!=2) return false;
            std::vector<std::pair<int,int>> red_pos = board.getPosByPiece(board::Piece::RED_DISC);
            std::vector<std::pair<int,int>> blue_pos = board.getPosByPiece(board::Piece::BLUE_DISC);
            if (!(red_pos.empty()) && (red_pos.size()==1) && (blue_pos.empty())) return true;
            return false;
        }

        /**
         * @brief Ritorna il tipo di pedina utilizzabile dal giocatore di turno
         * 
         * @return board::Piece pedina utilizzabile dal giocatore del turno attuale.
         * Ritorna la pedina vuota (board::Piece::EMPTY) se il gioco è finito.
         * 
         * Esempio:
         * board::Piece current_piece = situation.getPieceByTurn();
         */
        board::Piece getPieceByTurn() const {
            if (turn==1) return board::Piece::RED_DISC;
            if (turn==2) return board::Piece::BLUE_DISC;
            return board::Piece::EMPTY;
        }

        /** Ritorna true se m è una mossa valida nell'attuale situazione di gioco.
         * 
         * @param m una mossa
         * @return true se m è una mossa valida, false altrimenti (anche se il gioco è terminato)
         * 
         * Da utilizzare spesso nel seguente modo
         * if (situation.isValid(m)) ... 
         */
        bool isValid(move::Move m) const {
            if (m.kind == move::MoveKind::RESIGN) return true;
            if (m.action.piece!=getPieceByTurn()) return false;
            if (m.kind == move::MoveKind::SWAP) {
                if (!pieRule()) return false;            
                if (board.getPieceAtPos(m.action.position)!=board::Piece::RED_DISC) return false;
                return true;
            }    
            if (board.getPieceAtPos(m.action.position)!=board::Piece::EMPTY) return false;
            return true;
        }

        /**
         * @brief Funzione che ritorna la lista di mosse valide 
         * a partire dalla situazione corrente.
         * 
         * @return std::vector<move::Move> vettore di mosse valide in una situazione.
         * 
         * Esempio:
         * std::vector<move::Move> mosse_valide = situation.validMoves();
         */
        std::vector<move::Move> validMoves() const {
            std::vector<move::Move> valid_moves;
            move::Move resign_move;
            valid_moves.push_back(resign_move);
            if (pieRule()) {
                std::vector<std::pair<int,int>> red_pos = board.getPosByPiece(board::Piece::RED_DISC);
                std::pair<int,int> swap_pos = red_pos.at(0);
                move::Action swap_action(move::ActionKind::SWAP, board::Piece::BLUE_DISC, swap_pos);
                move::Move swap_move(move::MoveKind::SWAP, swap_action);
                valid_moves.push_back(swap_move);  
            }
            std::vector<std::pair<int,int>> free_pos = board.getPosByPiece(board::Piece::EMPTY);
            for (std::pair<int,int> pos : free_pos) {
                move::Action add_action(move::ActionKind::ADD, board::Piece::BLUE_DISC, pos);
                move::Move add_move(move::MoveKind::ADD, add_action);
                valid_moves.push_back(add_move);
            }
            return valid_moves;
        }

        /**
         * @brief Restituisce la situazione che si ottiene applicando una data
         * mossa alla situazione corrente
         * 
         * @param m mossa da applicare
         * @return Situation situazione corrente
         * @throws InvalidArgumentException se il gioco è terminato o se la mossa non è valida
         * 
         * Esempio:
         * move::Move m = situation.validMoves().at(2);
         * game::Situation next_situation = situation.next(m);
         * Si prende una mossa valida e la si applica alla configurazione, ottenendo una nuova situation
         */
        Situation next(move::Move m) const {
            if (turn<1) throw std::invalid_argument( "Invalid Move, the Game is Over." );
            if (!isValid(m)) throw std::invalid_argument( "Invalid Move." );                     
            board::HexBoard b(board);
            int t = turn;
            if (m.kind == move::MoveKind::RESIGN) {
                t-=3;
                return Situation(b, t);
            }
            if (m.kind == move::MoveKind::SWAP) {
                b.swapPiece(m.action.position);
                t = 3-t;
                return Situation(b, t);
            }
            b.addPiece(m.action.piece, m.action.position);
            if (b.checkWin(t)) {
                t = -t;
                return Situation(b, t);
            }
            t = 3-t;   
            return Situation(b, t);
        }
    };
}

#endif