//
// Created by haz on 4/16/21.
//


#include <algorithm>
#include <iostream>
#include "G_Checkers.h"
using std::cout;
using std::endl;
using std::vector;
using std::move;
using std::pair;

G_Checkers::G_Checkers() {
}

void G_Checkers::createBoard() {
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

vector<vector<optional<Piece>>> G_Checkers::getBoard() const {
    return board;
}

bool G_Checkers::isPiece(int x, int y) const {
    if (board[x][y]) {
        return true;
    }
    return false;
}

bool G_Checkers::validateMove(Player player, G_Move move) const {
    int xJ, yJ;
    int x0 = move.x0;
    int y0 = move.y0;
    int x1 = move.x1;
    int y1 = move.y1;

    // User clicked an empty space or an opposing player's piece
    if (!board[x0][y0] || board[x0][y0]->getPlayer() != player) {
        return false;
    }

    // If the move is too large, i.e. greater than two spaces
    if (abs(x0 - x1) > 2 || abs(y0 - y1) > 2) {
        return false;
    }

    // There is already a piece on the ending space
    if (board[x1][y1]) {
        return false;
    }

    // If either player is trying to move backwards without a king
    if ((player == PLAYER1 && x1 >= x0) || (player == PLAYER2 && x1 <= x0)) {
        if (!board[x0][y0]->isKing()) {
            return false;
        }
    }

    // The move involves jumping over a piece
    if (abs(x0 - x1) == 2 && abs(y0 - y1) == 2) {
        // Coordinates of piece being jumped over
        (x0 > x1) ? xJ = x0 - 1 : xJ = x0 + 1;  // if x0 > x1 then xJ = x0 - 1 otherwise xJ = x0 + 1
        (y0 > y1) ? yJ = y0 - 1 : yJ = y0 + 1;  // if y0 > y1 then yJ = y0 - 1 otherwise yJ = y0 + 1

        // There is no piece to jump over or the player is trying to jump over their own piece
        if (!board[xJ][yJ] || board[xJ][yJ]->getPlayer() == player) {
            return false;
        }
    }

    return true;
}

void G_Checkers::movePiece(G_Move move) {
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