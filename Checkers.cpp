#include <algorithm>
#include "Checkers.h"
using std::cout;
using std::endl;
using std::vector;
using std::move;
using std::pair;


Checkers::Checkers() {
    createBoard();
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
                          "- To make a move click on the piece you wish to move and then",
                          "  click on the space you want to move it to.",
                          "- This version of checkers does not support making multiple", "  jumps in one turn :( .",
                          "- If one of your pieces reaches the opposite side of the board", "  it becomes a king.",
                          "- King pieces are distinguished by a crown symbol", "  appearing on the piece",
                          "- King pieces can move both forwards and backwards.",
                          "- A player wins when they have captured all of their", "  opponent's pieces.",
                          "Press 's' to start playing"};
    return rules;
}


vector<vector<optional<Piece>>> Checkers::getBoard() const {
    return board;
}


bool Checkers::validateMove(Player player, Move move) const {
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

    // If the move is vertical or horizontal
    if (x0 == x1 || y0 == y1) {
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


void Checkers::movePiece(Move move) {
    int xJ, yJ;
    int x0 = move.x0;
    int y0 = move.y0;
    int x1 = move.x1;
    int y1 = move.y1;

    optional<Piece> movingPiece = board[x0][y0];
    movingPiece->setPos(x1, y1);

    board[x0][y0] = nullopt;  // "Pick up" moving piece
    board[x1][y1] = movingPiece;  // "Place" the moving piece on its new space
    board[x1][y1]->checkMakeKing();

    // The move involves jumping over a piece
    if (abs(x0 - x1) == 2 && abs(y0 - y1) == 2) {
        (x0 > x1) ? xJ = x0 - 1 : xJ = x0 + 1;  // if x0 > x1 then xJ = x0 - 1 otherwise xJ = x0 + 1
        (y0 > y1) ? yJ = y0 - 1 : yJ = y0 + 1;  // if y0 > y1 then yJ = y0 - 1 otherwise yJ = y0 + 1
        board[xJ][yJ] = nullopt;  // Remove the captured piece
        if (board[xJ][yJ]->getPlayer() == PLAYER1) {
            --p1PieceCount;
        } else {
            --p2PieceCount;
        }
    }
}


bool Checkers::checkWin() const {
    if (p1PieceCount == 0 || p2PieceCount == 0) {
        return true;  // Someone has won
    }
    return false;
}


string Checkers::getResults() const {
    if (p1PieceCount < p2PieceCount) {
        return "PLAYER 2 WINS! Thanks for playing";
    }
    return "PLAYER 1 WINS! Thanks for playing";
}

