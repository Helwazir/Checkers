#ifndef M4OEP_GRAPHICS_CHECKERSPIECE_H
#define M4OEP_GRAPHICS_CHECKERSPIECE_H

#include "circle.h"

class CheckersPiece : public Circle {
private:
    bool king;

public:
    /*
     * Requires: Nothing
     * Modifies: king
     * Effects: Creates a CheckersPiece object with it's king field initialized to false.
     */
    CheckersPiece();

    /*
     * Requires: whether or noth the piece is a king
     * Modifies: king
     * Effects: reates a CheckersPiece object with it's king field initialized to the given value
     */
    explicit CheckersPiece(bool king);

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the CheckersPiece. If the piece is not a king then it is drawn as a solid color. If the piece is
     *          a king then a black crown is drawn on top of it.
     */
    void draw() const;
};


#endif //M4OEP_GRAPHICS_CHECKERSPIECE_H
