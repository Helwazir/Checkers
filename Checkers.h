//
// Created by haz on 4/13/21.


#ifndef M4OEP_GRAPHIC_CHECKERS_H
#define M4OEP_GRAPHIC_CHECKERS_H


#include <optional>
#include <vector>
#include "BoardGame.h"
#include "Move.h"
#include "Piece.h"
using std::optional;
using std::nullopt;
using std::make_optional;
using std::istream;
using std::vector;
using std::string;

/* Class Checkers models the board game checkers. It has fields for the number of pieces player one has captured,
 * the number of pieces player two has captured, and a two dimensional vector of pieces representing the game board. */
class Checkers : public BoardGame {
private:
    int playerOneCaptured = 0;
    int playerTwoCaptured = 0;
    vector<vector<optional<Piece>>> board;

public:
    /* CONSTRUCTOR */
    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Calls the BoardGame constructor with values specific to the game of checkers.
     */
    Checkers();

    /*
     * Requires: ostream
     * Modifies: Nothing
     * Effects: Prints the rules of the game.
     */
    void showRules(ostream &outs);

    /*
     * Requires: ostream
     * Modifies: board
     * Effects: Creates and populates a vector representing the board with pieces in the appropriate
     *          positions and with the appropriate owners.
     */
    void createBoard();


    /*
     * Requires: ostream
     * Modifies: Nothing
     * Effects: Prints the current state of the board along with numbered rows and lettered columns
     *          to make it easier for players to enter moves.
     */
    void showBoard(ostream &outs) const;


    vector<vector<optional<Piece>>> getBoard() const;

    vector<Piece> getPieces() const;



    /*
     * Requires: The current player, ostream, istream
     * Modifies: Nothing
     * Effects: Prompts the current player to enter a move and validates it. If the move is valid then
     *          it is returned as a Move struct. Otherwise, the user is prompted over and over until
     *          a valid move is entered.
     */
    Move getMove(Player player, ostream &outs, istream &ins);

    /*
     * Requires: The current player, and the move to be validated
     * Modifies: Nothing
     * Effects: Checks all cases in which the move would be considered an illegal checkers move.
     *          If the move does not meet any of the requirements of being invalid it is considered
     *          valid and the method returns true. If the move meets any of the requirements for being
     *          invalid then the method returns false.
     */
    bool validateMove(Player player, int rowStart, int colStart, int rowEnd, int colEnd) const;

    /*
     * Requires: The current player, and the move being performed
     * Modifies: board
     * Effects: Moves the Piece at the starting position given by move to the ending position given
     *          by move. If a piece is present at the ending position then the piece "jumps" over it
     *          and captures it. The move is validated before this method is called so the move is
     *          always valid and executed.
     */
    bool movePiece(Player player, int rowStart, int colStart, int rowEnd, int colEnd) ;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the number of player two's pieces that player one has captured.
     */
    int getPlayerOneCaptured() const;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the number of player one's pieces that player two has captured.
     */
    int getPlayerTwoCaptured() const;

    /*
     * Requires: The current player
     * Modifies: Either playerOneCaptured or playerTwoCaptured
     * Effects: Increments the number of the opposing player's pieces captured of the current player by one.
     */
    void updatePieces(Player player);

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Checks to see if either player has won by capturing all 12 of the opposing player's pieces.
     *          Returns true if player one has won, returns false if player two has won, returns nullopt if
     *          neither player has won yet.
     */
    optional<bool> checkWin() const;

    /*
     * Requires: ostream, istream
     * Modifies: Everything
     * Effects: Runs a loop of game logic calling functions to perform different phases of the game. Alternates
     *          turns between players and prompts each user for their move. After each move checkWin() is called
     *          in order to check if the game has been won.
     */
    void play(ostream &outs, istream &ins) override;
};

#endif //M4OEP_GRAPHIC_CHECKERS_H
