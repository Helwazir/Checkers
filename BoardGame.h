//
// Created by haz on 4/13/21.
//

#ifndef M4OEP_GRAPHIC_BOARDGAME_H
#define M4OEP_GRAPHIC_BOARDGAME_H


#include <iostream>
using std::ostream;
using std::istream;

/* The BoardGame class represents the top level of a grid-based board game. */
class BoardGame{
private:
    int numPlayers;
    int boardRows;
    int boardCols;

public:
    /* CONSTRUCTORS */
    /*
     * Requires: Nothing
     * Modifies: numPlayers, boardRows, boardCols
     * Effects: Creates a BoardGame object with all fields initialized to their minimums.
     */
    BoardGame();
    /*
     * Requires: number of players, number of rows the board has, number of columns the board has
     * Modifies: numPlayers, boardRows, boardCols
     * Effects: Creates a BoardGame object with all fields initialized to the given values.
     */
    BoardGame(int numPlayers, int boardRows, int boardCols);

    /* GETTERS */
    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the number of players in the board game.
     */
    int getNumPlayers() const;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the number of rows that the board game has.
     */
    int getBoardRows() const;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the number of columns that the board game has.
     */
    int getBoardCols() const;

    /* SETTERS */
    /*
     * Requires: The number of players
     * Modifies: numberOfPlayers
     * Effects: Sets the number of players to the given value.
     */
    void setNumPlayers(int numberOfPlayers);

    /*
     * Requires: The number of rows
     * Modifies: boardRows
     * Effects: Sets the number of rows the board game has.
     */
    void setBoardRows(int boardRows);

    /*
     * Requires: The number of columns
     * Modifies: boardCols
     * Effects: Sets the number of rows the board game has.
     */
    void setBoardCols(int boardCols);

    /* Virtual function to play the board game */
    virtual void play(ostream &outs, istream &ins) = 0;

    static const int MIN_NUMBER_OF_PLAYERS = 1;
    static const int MIN_NUMBER_OF_ROWS = 1;
    static const int MIN_NUMBER_OF_COLS = 1;
};

#endif //M4OEP_GRAPHIC_BOARDGAME_H
