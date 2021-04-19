#include "Piece.h"
using std::string;

Piece::Piece() : player(nullopt), king(false) {
}


Piece::Piece(Player player, int x, int y) {
    this->player = player;
    xPos = x;
    yPos = y;
    king = false;
}


optional<Player> Piece::getPlayer() const {
    return player;
}


void Piece::setPos(int x, int y) {
    xPos = x;
    yPos = y;
}


void Piece::makeKing() {
    king = true;
}


bool Piece::isKing() const {
    return king;
}


void Piece::checkMakeKing() {
    if (!this->isKing()) {
        if (player == PLAYER1 && xPos == 0) { // Player1's piece must be on row index 0 to become a king
            this->makeKing();
        }
        else if (player == PLAYER2 && xPos == 7) { // Player2's piece must be on row index 7 to become a king
            this->makeKing();
        }
    }
}
