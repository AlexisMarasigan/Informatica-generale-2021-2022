/**
 * @file main.cpp
 * @brief esempi di utilizzo delle librerie del progetto
 * @date 07/06/2022 - ultimo aggiornamento
 * 
 */

#include<iostream>
#include "board.h"
#include "move.h"
#include "game.h"
#include "player.h"

int main() {
    /// Come inizializzare un oggetto di tipo Piece
    board::Piece piece = board::Piece::BLUE_DISC;
    board::HexBoard board(11); // Crea una board vuota 11x11
    board::HexBoard empty_board; // Crea una board vuota 0x0
    board::HexBoard copy_board(board); // Crea una board copiandone un'altra
    int size = board.getSize(); // Ottengo la dimensione di una board
    std::pair<int,int> p = std::make_pair(1, 2); 
    int p1 = p.first; // Prima coordinata, 1
    int p2 = p.second; // Seconda coordinate, 2
    bool x = board.isValidPos(p); // true
    board::Piece piece_ij = board.getPieceAtPos(std::make_pair(3,4)); // Pezzo in posizione (3,4)
    board.addPiece(piece, std::make_pair(5,6));
    board.addPiece(piece, std::make_pair(6,6));
    std::vector<std::pair<int,int>> blue_pos = board.getPosByPiece(piece); // Tutte le posizioni con pedine blu
    std::cout << "La scacchiera contiene " << blue_pos.size() << " pedine blu.\n";
    std::vector<std::pair<int,int>> adj_pos = board.getAdjacentPos(std::make_pair(10,0)); // Mostra le posizioni adiacenti
    std::cout << "La scacchiera contiene " << adj_pos.size() << " posizioni adiacenti a (10,0).\n";
    board::HexBoard small_board(3); // Creo una piccola scacchiera 3x3 e la riempio
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(0,0));
    small_board.addPiece(board::Piece::RED_DISC, std::make_pair(0,1));
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(0,2));
    small_board.addPiece(board::Piece::RED_DISC, std::make_pair(1,0));
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(1,1));
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(1,2));
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(2,0));
    small_board.addPiece(board::Piece::BLUE_DISC, std::make_pair(2,1));
    small_board.addPiece(board::Piece::RED_DISC, std::make_pair(2,2));
    if (small_board.checkWin(1))    // Cerco di capire chi ha vinto
        std::cout << "Vince il Rosso!\n";
    else
        std::cout << "Vince il Blu!\n";
    /// Esempi di utilizzo di Action e Move
    move::Action a_add(move::ActionKind::ADD, piece, p); // Creazione dell'azione ADD
    move::Move m_add(move::MoveKind::ADD, a_add); // Creazione della mossa ADD
    move::MoveKind m_kind = m_add.kind; // Tipo della mossa (move::MoveKind::ADD)
    std::pair<int,int> position_add = m_add.action.position; // Posizione della mossa
    move::Action a_add_2(move::ActionKind::ADD, board::Piece::BLUE_DISC, std::make_pair(1,2)); // Creo un'azione equivalente alla prima
    if (a_add==a_add_2) std::cout << "Azioni equivalenti\n"; // Verifico che le due azioni siano equivalenti
    /// Esempi di utilizzo di oggetti Situation per configurazioni di gioco
    board::HexBoard new_board(11); // Creo una nuova board vuota 11x11
    new_board.addPiece(board::Piece::RED_DISC, m_add.action.position); // Simulo la prima mossa (Rosso) sulla board
    game::Situation situation(new_board, 2); // Creo una Situation, turn=2 (tocca al blu)
    if (situation.getPieceAtPos(p)==board::Piece::RED_DISC) // Verifico che ci sia una pedina rossa in posizione p
        std::cout << "Pedina rossa\n";
    if (situation.pieRule()) // Verifico che sia possibile utilizzare la pie rule
        std::cout << "Pie rule utilizzabile\n";
    if (situation.getPieceByTurn()==board::Piece::BLUE_DISC) // Ottengo il pezzo utilizzabile dal giocatore al turno corrente
        std::cout << "Tocca al blu\n";
    if (!situation.isValid(m_add)) // Verifico che non posso ripetere la stessa mossa
        std::cout << "Mossa non valida.\n";
    std::vector<move::Move> mosse_valide = situation.validMoves(); // Ottengo il vettore delle mosse valide in questa configurazione
    std::cout << "Mosse valide: " << mosse_valide.size() << std::endl; // Numero di mosse valide: 120 ADD + 1 SWAP + 1 RESIGN
    game::Situation new_situation = situation.next(mosse_valide.at(5)); // Applico una mossa valida per ottenere una nuova situazione
    if (new_situation.turn>0) // Verifico che il gioco non sia già terminato
        std::cout << "Il gioco va avanti.\n";












    //player::Player p;
}