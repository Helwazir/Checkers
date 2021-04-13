//
// Created by haz on 4/13/21.
//

#include "BoardGame.h"

BoardGame::BoardGame() : numPlayers(MIN_NUMBER_OF_PLAYERS), boardRows(MIN_NUMBER_OF_ROWS), boardCols(MIN_NUMBER_OF_COLS) {
}

BoardGame::BoardGame(int numPlayers, int boardRows, int boardCols) {
    setNumPlayers(numPlayers);
    setBoardRows(boardRows);
    setBoardCols(boardCols);
}

int BoardGame::getNumPlayers() const {
    return numPlayers;
}

int BoardGame::getBoardRows() const {
    return boardRows;
}

int BoardGame::getBoardCols() const {
    return boardCols;
}

void BoardGame::setNumPlayers(int numPlayers) {
    if (numPlayers >= MIN_NUMBER_OF_PLAYERS) {
        this->numPlayers = numPlayers;
    } else {
        this->numPlayers = MIN_NUMBER_OF_PLAYERS;
    }
}

void BoardGame::setBoardRows(int boardRows) {
    if (boardRows >= MIN_NUMBER_OF_ROWS) {
        this->boardRows = boardRows;
    } else {
        this->boardRows = MIN_NUMBER_OF_ROWS;
    }
}

void BoardGame::setBoardCols(int boardCols) {
    if (boardCols >= MIN_NUMBER_OF_COLS) {
        this->boardCols = boardCols;
    } else {
        this->boardCols = MIN_NUMBER_OF_COLS;
    }
}
