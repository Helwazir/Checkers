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

    explicit CheckersPiece(bool king);

    void draw() const;
};


#endif //M4OEP_GRAPHICS_CHECKERSPIECE_H
