//
// Created by haz on 4/16/21.
//

#include "CheckersPiece.h"
#include "graphics.h"

CheckersPiece::CheckersPiece() : Circle(32) {
    this->king = false;
}

CheckersPiece::CheckersPiece(bool king) : Circle(32) {
    this->king = king;
}

void CheckersPiece::draw() const {
    int radius = getRadius();
    Circle::draw();

    if (king) {
        glColor3f(0, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex2i(center.x - (radius / 2), center.y - (radius / 2));
        glVertex2i(center.x - (radius / 2), center.y);
        glVertex2i(center.x, center.y);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2i(center.x + (getRadius() / 2), center.y - (getRadius() / 2));
        glVertex2i(center.x + (getRadius() / 2), center.y);
        glVertex2i(center.x, center.y);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2i(center.x, center.y - (getRadius() / 2));
        glVertex2i(center.x - (getRadius() / 2), center.y);
        glVertex2i(center.x + (getRadius() / 2), center.y);
        glEnd();
    }
}
