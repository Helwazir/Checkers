//
// Created by haz on 4/16/21.
//

#ifndef M4OEP_GRAPHICS_CHECKERSPIECE_H
#define M4OEP_GRAPHICS_CHECKERSPIECE_H

#include "circle.h"

class CheckersPiece : public Circle {
private:
    bool king;

public:
    CheckersPiece();
    CheckersPiece(int x, int y);
    CheckersPiece(int x, int y, bool king);
    bool isKing() const;
    void makeKing();

    void draw() const;
};


#endif //M4OEP_GRAPHICS_CHECKERSPIECE_H
