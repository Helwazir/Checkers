//
// Created by haz on 4/13/21.
//

#include "BoardGame.h"
#include "Checkers.h"
#include "Piece.h"
#include "graphics.h"
#include "shape.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <time.h>
#include "G_Checkers.h"
#include <memory>
#include <vector>
#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;
using std::istream;

using namespace std;

enum Screen {Start, Second, End};
Screen state = Start;
Player player = PLAYER1;
vector<vector<optional<Piece>>> board;
Checkers checkers;
G_Checkers G_check;
GLdouble width, height, edgeLength;
int x_0, y_0, x_1, y_1;
bool clicked = false;
Rect user;
int wd;


// TODO: Completely re-write move validation in Checkers.cpp

void initUser() {
    // centered in the top left corner of the graphics window
    user = Rect(color(1, 0, 0), 0, 0, dimensions(20, 20));
}

void init() {
    checkers = Checkers();
    checkers.createBoard();
    width = 600;
    height = 600;
    edgeLength = height / 8;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    /*
     * Draw Here
     */

    // Draw Checkers Board
    int i, j;
    vector<Rect> spaces;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            Rect space = Rect(dimensions(edgeLength, edgeLength));
            space.setCenter((i * 75) + (75/2), (j * 75) + (75/2));
            if ((i + j) % 2 == 0) {
                space.setColor(color(1, 1, 1));
            } else {
                space.setColor(color(0, 0, 0));
            }
            spaces.push_back(space);
            space.draw();
        }
    }

    // Highlight space
    for (Rect &space : spaces) {
        if (space.isOverlapping(user)) {
            space.setColor(color(0.5, 0.5, 0.5));
            space.draw();
        }
    }

    // Draw pieces
    vector<Circle> pieces;
    board = checkers.getBoard();
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (board[i][j] != nullopt) {
                Circle piece = Circle(32);
                piece.setCenter((j * 75) + (75/2), (i * 75) + (75/2));

                if (board[i][j]->getPlayer() == PLAYER1) {;
                    piece.setColor(color(0.75, 0, 0));
                } else {
                    piece.setColor(color(0.3, 0.19, 0.08));
                }
                pieces.push_back(piece);
                piece.draw();
            }
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_UP:
            break;
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    user.setCenterX(x);
    user.setCenterY(y);
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    board = checkers.getBoard();
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int spaceXPos = ceil(x / 75);
        int spaceYPos = ceil(y / 75);
        cout << spaceXPos << ", " << spaceYPos << endl;
        if (clicked == false) {
            x_0 = spaceXPos;
            y_0 = spaceYPos;
            clicked = true;
        } else {
            x_1 = spaceXPos;
            y_1 = spaceYPos;
            clicked = false;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (clicked == false) {
//            checkers.movePiece(PLAYER1, y_0, x_0, y_1, x_1);
            while (!checkers.validateMove(player, y_0, x_0, y_1, x_1)) {
                cout << "Invalid move, please make a different move" << endl;
            }
            if (checkers.validateMove(player, y_0, x_0, y_1, x_1)) {
                checkers.movePiece(player, y_0, x_0, y_1, x_1);

                if (player == PLAYER1) {
                    player = PLAYER2;
                } else {
                    player = PLAYER1;
                }
            } else {
                cout << "INVALID MOVE" << endl;
            }
            checkers.showBoard(cout);
        }
    }


    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Confettify!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

