//
// Created by haz on 4/16/21.
//


#include <algorithm>
#include <iostream>
#include "Checkers.h"
using std::cout;
using std::endl;
using std::vector;
using std::move;
using std::pair;

Checkers::Checkers() {
}

void Checkers::createBoard() {
    int i, j;
    int rows = 8;
    int cols = 8;

    /* Creates an empty 8x8 board */
    vector<vector<optional<Piece>>> board;
    for (i = 0; i < rows; ++i) {
        vector<optional<Piece>> col(cols);
        board.push_back(col);
    }

    /* Populate board with each player's pieces in the correct spots */
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if ((i + j) % 2 == 1 && i < 3) {
                Piece piece = Piece(PLAYER2, i, j);
                board[i][j] = piece; // Player2
            }
            else if ((i + j) % 2 == 1 && i >= 5) {
                Piece piece = Piece(PLAYER1, i, j);
                board[i][j] = piece; // Player11
            }
        }
    }
    this->board = board;
}

vector<string> Checkers::getRules() const {
    vector<string> rules {"Checkers Rules:",
                          "- Player 1's pieces are red, Player 2's pieces are brown.",
                          "- To make a move enter the coordinates of piece you want to move",
                          " and the coordinates of the space you want to move to",
                          "- If you want to jump over an enemy piece and capture it",
                          " enter the coordinates of the enemy piece",
                          "- This version of checkers does not support making multiple", "jumps in one turn :( .",
                          "- If one of your pieces reaches the opposite side of the board", "it becomes a king.",
                          "- King pieces are distinguished by an uppercase letter marking", "the piece: (P) or (C).",
                          "- King pieces can move both forwards and backwards.",
                          "- A player wins when they have either captured all of the", "opponent's pieces.",
                          "Press 's' to start playing"};
//    string rules = "Checkers Rules:\n"
//                   "- Player 1's pieces are marked as (p), Player 2's pieces are marked as (c).\n"
//                   "- To make a move enter the coordinates of piece you want to move i.e. \"a1\".\n"
//                   "  and the coordinates of the space you want to move to i.e. \"b2\".\n"
//                   "- If you want to jump over an enemy piece and capture it enter the coordinates of the enemy piece, not the space you jump to.\n"
//                   "- This version of checkers does not support making multiple jumps in one turn :( .\n"
//                   "- If one of your pieces reaches the opposite side of the board it becomes a king.\n"
//                   "- King pieces are distinguished by an uppercase letter marking the piece: (P) or (C).\n"
//                   "- King pieces can move both forwards and backwards.\n"
//                   "- A player wins when they have either captured all of the opponent's pieces.\n"
//                   "- To see the rules again enter \"R\" as both of your moves.\n"
//                   "- To forfeit the game enter \"Q\" as both of your move.\n"
//                   "Press 's' to start playing";
    return rules;
}

vector<vector<optional<Piece>>> Checkers::getBoard() const {
    return board;
}

bool Checkers::isPiece(int x, int y) const {
    if (board[x][y]) {
        return true;
    }
    return false;
}

bool Checkers::validateMove(Player player, G_Move move) const {
    int xJ, yJ;
    int x0 = move.x0;
    int y0 = move.y0;
    int x1 = move.x1;
    int y1 = move.y1;

    // User clicked an empty space or an opposing player's piece
    if (!board[x0][y0] || board[x0][y0]->getPlayer() != player) {
        cout << "User clicked an empty space or an opposing player's piece" << endl;
        return false;
    }

    // If the move is too large, i.e. greater than two spaces
    if (abs(x0 - x1) > 2 || abs(y0 - y1) > 2) {
        cout << "If the move is too large, i.e. greater than two spaces" << endl;
        return false;
    }

    // There is already a piece on the ending space
    if (board[x1][y1]) {
        cout << "There is already a piece on the ending space" << endl;

        return false;
    }

    // If either player is trying to move backwards without a king
    if ((player == PLAYER1 && x1 >= x0) || (player == PLAYER2 && x1 <= x0)) {
        if (!board[x0][y0]->isKing()) {
            cout << "If either player is trying to move backwards without a king" << endl;
            return false;
        }
    }

    // The move involves jumping over a piece
    if (abs(x0 - x1) == 2 && abs(y0 - y1) == 2) {
        cout << "The move involves jumping over a piece" << endl;

        // Coordinates of piece being jumped over
        (x0 > x1) ? xJ = x0 - 1 : xJ = x0 + 1;  // if x0 > x1 then xJ = x0 - 1 otherwise xJ = x0 + 1
        (y0 > y1) ? yJ = y0 - 1 : yJ = y0 + 1;  // if y0 > y1 then yJ = y0 - 1 otherwise yJ = y0 + 1

        // There is no piece to jump over or the player is trying to jump over their own piece
        if (!board[xJ][yJ] || board[xJ][yJ]->getPlayer() == player) {
            cout << "" << endl;

            return false;
        }
    }

    cout << "Move is valid" << endl;
    return true;
}

void Checkers::movePiece(G_Move move) {
    int xJ, yJ;
    int x0 = move.x0;
    int y0 = move.y0;
    int x1 = move.x1;
    int y1 = move.y1;

    optional<Piece> movingPiece = board[x0][y0];

    board[x0][y0] = nullopt;  // "Pick up" moving piece
    board[x1][y1] = movingPiece;  // "Place" the moving piece on its new space

    // The move involves jumping over a piece
    if (abs(x0 - x1) == 2 && abs(y0 - y1) == 2) {
        (x0 > x1) ? xJ = x0 - 1 : xJ = x0 + 1;  // if x0 > x1 then xJ = x0 - 1 otherwise xJ = x0 + 1
        (y0 > y1) ? yJ = y0 - 1 : yJ = y0 + 1;  // if y0 > y1 then yJ = y0 - 1 otherwise yJ = y0 + 1
        board[xJ][yJ] = nullopt;  // Remove the captured piece
    }
}