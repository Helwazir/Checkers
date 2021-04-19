#ifndef M4OEP_GRAPHICS_CHECKERS_H
#define M4OEP_GRAPHICS_CHECKERS_H

#include <optional>
#include <vector>
#include <iterator>
#include "Move.h"
#include "Piece.h"

using std::optional;
using std::nullopt;
using std::make_optional;
using std::istream;
using std::vector;
using std::string;

class Checkers {
private:
    int p1PieceCount = 12;
    int p2PieceCount = 12;
    vector<vector<optional<Piece>>> board;

public:
    /*
     * Requires: Nothing
     * Modifies: Board
     * Effects: Calls createBoard in order to populate the board with both player's pieces in the appropriate spots.
     */
    Checkers();

    /*
     * Requires: Nothing
     * Modifies: Board
     * Effects: Creates a two-dimensional vector of optional pieces to represent the game board.
     */
    void createBoard();

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns a vector of strings containing the rules, used for displaying the rules before the game.
     */
    vector<string> getRules() const;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the two-dimensional vector of the board
     */
    vector<vector<optional<Piece>>> getBoard() const;

    /*
     * Requires: The current player and the move being performed
     * Modifies: Nothing
     * Effects: Returns true if the proposed move is legal, otherwise returns false.
     */
    bool validateMove(Player player, Move move) const;

    /*
     * Requires: The move being performed
     * Modifies: board
     * Effects: Performs the proposed move. If the move involves capturing one of the opponent's pieces then the
     *          captured piece is removed from the board.
     */
    void movePiece(Move move);

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns true if one of the players has captured all of their opponent's pieces, otherwise returns false.
     */
    bool checkWin() const;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns a string declaring victory for the winning player.
     */
    string getResults() const;
};

#endif //M4OEP_GRAPHICS_CHECKERS_H
