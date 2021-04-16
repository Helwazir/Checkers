//
// Created by haz on 4/13/21.
//

#ifndef M4OEP_GRAPHIC_PIECE_H
#define M4OEP_GRAPHIC_PIECE_H

#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;
using std::istream;
#include <iostream>
using std::ostream;

/* Enum to set the owner of the piece */
enum Player {PLAYER1, PLAYER2};

/*
 * The Piece class represents a piece on a checkers board. It has fields for the owner of the piece and whether or not
 * the piece is a king.
 */
class Piece {
private:
    int xPos;
    int yPos;
    optional<Player> player;
    bool king;

public:

    /* CONSTRUCTORS */
    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Creates a Piece object with player initialized to nullopt and king set to false.
     */
    Piece();

    /*
     * Requires: Which player the piece belongs to
     * Modifies: player
     * Effects: Sets the owner of the piece.
     */
    explicit Piece(Player player, int x, int y);

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the owner of the piece. If the piece is nullopt then there is no piece.
     */
    optional<Player> getPlayer() const;

    /*
     * Requires: The x and y coordinates of the piece
     * Modifies: xPos, yPos
     * Effects: Sets xPos and yPos to the current position of the piece.
     */
    void setPos(int x, int y);

    /*
     * Requires: Nothing
     * Modifies: king
     * Effects: Makes the piece a king.
     */
    void makeKing();

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns true if the piece is a king, otherwise false.
     */
    bool isKing() const;

    /*
     * Requires: Nothing
     * Modifies: king
     * Effects: Checks whether or not a player's piece is in the correct spot to become a king. If it is then the
     *          piece is made a king.
     */
    void checkMakeKing();

};


#endif //M4OEP_GRAPHIC_PIECE_H
