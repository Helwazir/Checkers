//
// Created by haz on 4/13/21.
//

#include "Piece.h"
using std::string;

Piece::Piece() : player(nullopt), king(false) {
}

Piece::Piece(Player player, int x, int y) {
    this->player = player;
    king = false;
}

optional<Player> Piece::getPlayer() const {
    return player;
}

int Piece::getXPos() const {
    return xPos;
}

int Piece::getYPos() const {
    return yPos;
}

void Piece::makeKing() {
    king = true;
}

bool Piece::isKing() const {
    return king;
}

void Piece::checkMakeKing(Player player, int row) {
    if (!this->isKing()) {
        if (player == PLAYER1 && row == 0) { // Player1's piece must be on row index 0 to become a king
            this->makeKing();
        }
        else if (player == PLAYER2 && row == 7) { // Player2's piece must be on row index 7 to become a king
            this->makeKing();
        }
    }
}

ostream& operator << (ostream& outs, const optional<Piece> &piece) {
    string pieceStr;
    if (piece) {
        if (piece->getPlayer() == PLAYER1) {
            pieceStr = "(p)"; // Player1 piece
        } else {
            pieceStr = "(c)"; // Player2 piece
        }
        if (piece->isKing()) { // If the piece is a king then change the letter denoting the owner to uppercase
            pieceStr[1] = toupper(pieceStr[1]);
        }
        outs << pieceStr;
    } else {
        outs << " - ";  // Empty spot
    }
    return outs;
}