//
// Created by haz on 4/13/21.
//

#ifndef M4OEP_GRAPHIC_MOVE_H
#define M4OEP_GRAPHIC_MOVE_H


#include <string>
using std::string;

/* struct Move models a player's move. It has fields to store the player's move in terms of it's string
 * value and fields for int coordinates of the starting position and ending position of the desired move.*/
struct Move {
    // Player's move in terms of string coordinates(i.e. "a1", "b2")
    string startPos;
    string endPos;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Converts the row position in startPos to the equivalent int coordinate on the board and returns it.
     */
    int getRowStart() {
        return (8 - (startPos[1] - '0'));
    }

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Converts the col position in startPos to the equivalent int coordinate on the board and returns it.
     */
    int getColStart() {
        return (tolower(startPos[0]) - 97);
    }

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Converts the row position in endPos to the equivalent int coordinate on the board and returns it.
     */
    int getRowEnd() {
        return (8 - (endPos[1] - '0'));
    }

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Converts the col position in endPos to the equivalent int coordinate on the board and returns it.
     */
    int getColEnd() {
        return (tolower(endPos[0]) - 97);
    }
};

#endif //M4OEP_GRAPHIC_MOVE_H
