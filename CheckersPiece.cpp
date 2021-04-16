//
// Created by haz on 4/16/21.
//

#include "CheckersPiece.h"
#include "graphics.h"

CheckersPiece::CheckersPiece() : Circle(32) {
}
CheckersPiece::CheckersPiece(int x, int y) : Circle(x, y, 32) {
}
CheckersPiece::CheckersPiece(int x, int y, bool king) : Circle(x, y, 32) {
    this->king = king;
}


bool CheckersPiece::isKing() const {
    return king;
}
void CheckersPiece::makeKing() {
    king = true;
}

void CheckersPiece::draw() const {
    // Set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // Draw circle as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of circle
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + (getRadius() * cos(i)),
                   center.y + (getRadius() * sin(i)));
    }
    // End Triangle Fan

    glColor3f(0, 0, 0);



    glEnd();
}

