//
// Created by haz on 4/13/21.
//

#include <algorithm>
#include <iostream>
#include "Checkers.h"
using std::cout;
using std::endl;
using std::vector;
using std::move;

vector<Piece> pieces;

Checkers::Checkers() : BoardGame(2, 8, 8) {
}

void Checkers::showRules(ostream &outs) {
    outs << "Checkers Rules:" << endl;
    outs << "- Player 1's pieces are marked as (p), Player 2's pieces are marked as (c)." << endl;
    outs << "- To make a move enter the coordinates of piece you want to move i.e. \"a1\"." << endl;
    outs << "  and the coordinates of the space you want to move to i.e. \"b2\"." << endl;
    outs << "- If you want to jump over an enemy piece and capture it enter the coordinates of the enemy piece, not the space you jump to." << endl;
    outs << "- This version of checkers does not support making multiple jumps in one turn :( ." << endl;
    outs << "- If one of your pieces reaches the opposite side of the board it becomes a king." << endl;
    outs << "- King pieces are distinguished by an uppercase letter marking the piece: (P) or (C)." << endl;
    outs << "- King pieces can move both forwards and backwards." << endl;
    outs << "- A player wins when they have either captured all of the opponent's pieces." << endl;
    outs << "- To see the rules again enter \"R\" as both of your moves." << endl;
    outs << "- To forfeit the game enter \"Q\" as both of your move." << endl << endl;
}

void Checkers::createBoard() {
    int i, j;
    int rows = getBoardRows();
    int cols = getBoardCols();


    /* Creates an empty 8x8 board */
    vector<vector<optional<Piece>>> board;
    for (i = 0; i < rows; ++i) {
        vector<optional<Piece>> col(cols);
        board.push_back(col);
    }

    /* Populate board with each player's pieces in the correct spots */

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1 && i < 3) {
                Piece piece = Piece(PLAYER2, i, j);
                board[i][j] = piece; // Player 2
                pieces.push_back(piece);
            } else if ((i + j) % 2 == 1 && i >= 5) {
                Piece piece = Piece(PLAYER1, i, j);
                board[i][j] = piece; // Player 2
                pieces.push_back(piece);
            }
        }
    }
    this->board = board;
}


void Checkers::showBoard(ostream &outs) const {
    int i, j;
    for (i = 0; i < 8; ++i) {
        outs << 8 - i << "| ";
        for (j = 0; j < 8; ++j) {
            outs << board[i][j];
        }
        outs << endl;
    }
    outs << " -------------------------" << endl;
    outs << "    A  B  C  D  E  F  G  H" << endl;
}

vector<vector<optional<Piece>>> Checkers::getBoard() const {
    return board;
}

vector<Piece> Checkers::getPieces() const {
    return pieces;
}


Move Checkers::getMove(Player player, ostream &outs, istream &ins) {
    Move move;
    cout << "Enter the location of the piece you want to move: ";
    ins >> move.startPos;
    cout << "Enter the location of the space you want to move to: ";
    ins >> move.endPos;

    if (tolower(move.startPos[0]) == 'q' || tolower(move.startPos[0]) == 'r') { // Return the move before validation if the player wants to quit or see the rules
        return move;
    }
//    while (!validateMove(player, move)) { // While the move is invalid prompt the player to enter a valid move
//        outs << "Invalid move, please enter a valid move" << endl;
//        cout << "Enter the location of the piece you want to move: ";
//        ins >> move.startPos;
//        cout << "Enter the location of the space you want to move to: ";
//        ins >> move.endPos;
//    }
    return move;
}

bool Checkers::validateMove(Player player, int rowStart, int colStart, int rowEnd, int colEnd) const {

    int newRowEnd = (rowEnd * 2) - rowStart;
    int newColEnd = (colEnd * 2) - colStart;

    optional<Piece> movingPiece = board[rowStart][colStart]; // Piece being moved
    optional<Piece> endPiece = board[rowEnd][colEnd]; // Spot the piece is trying to be moved to
    optional<Piece> diagonalEndPiece = board[newRowEnd][newColEnd]; // The spot diagonal from the spot being moved to (jumping spot)

    // If any of the indices of either the starting position or the ending position are less than 0
    if (rowStart < 0 || colStart < 0 || rowEnd < 0 || colEnd < 0) {
        return false;
    }
    // If the move is too far, check if too far for king too
    if(abs(rowStart - rowEnd) > 1 || abs(colStart - colEnd) > 1) {
        if (movingPiece->isKing() && (abs(rowStart - rowEnd) > 2 || abs(colStart - colEnd) > 2)) {
            return false;
        }
        return false;
    }
        // If the player is trying to move backwards
    else if (player == PLAYER1 && rowStart - rowEnd < 1) {
        cout << "player1 is trying to move backwards" << endl;
        return false;
    }
        // If the computer is trying to move backwards
    else if (player == PLAYER2 && rowStart - rowEnd > 1) {
        cout << "player2 is trying to move backwards" << endl;

        return false;
    }
        // If the player is trying to move a piece that isn't theirs
    else if (player != movingPiece->getPlayer()) {
        cout << "player is trying to move a piece that isn't theirs" << endl;

        return false;
    }
        // If the player is trying to move a onto a space already occupied by one of their pieces
    else if (player == endPiece->getPlayer()) {
        cout << "player is trying to move a onto a space already occupied by one of their pieces" << endl;
        return false;
    }
        // If the player is trying to capture a piece but there is no spot to jump to
    else if(player != endPiece->getPlayer() && diagonalEndPiece != nullopt) {
        cout << "player is trying to capture a piece but there is no spot to jump to" << endl;

        return false;
    }
    return true;
}

bool Checkers::movePiece(Player player, int rowStart, int colStart, int rowEnd, int colEnd) {
//    int rowStart = move.getRowStart();
//    int colStart = move.getColStart();
//    int rowEnd = move.getRowEnd();
//    int colEnd = move.getColEnd();

    optional<Piece> movingPiece = board[rowStart][colStart];
    optional<Piece> endPiece = board[rowEnd][colEnd];

    if (endPiece) {
        /* Update ending space indices */
        int newRowEnd = (rowEnd * 2) - rowStart;
        int newColEnd = (colEnd * 2) - colStart;
        optional<Piece> diagonalEndPiece = board[newRowEnd][newColEnd];

        /* If the ending space has an opponents piece and the diagonal space is empty */
        if (endPiece->getPlayer() != player && !diagonalEndPiece) {
            board[rowStart][colStart] = nullopt;    // Take piece from original spot
            board[rowEnd][colEnd] = nullopt;    // Capture piece and remove from board
            board[newRowEnd][newColEnd] = movingPiece;    // Place original piece on the new space

            updatePieces(player); // Update the pieces captured of the current player
            board[newRowEnd][newColEnd]->checkMakeKing(player, newRowEnd); // Check if the moved piece is eligible to become a king
        }
    } else { // The ending spot is empty
        board[rowStart][colStart] = nullopt;    // Take piece from original spot..
        board[rowEnd][colEnd] = movingPiece;  // And place it on the new space
        board[rowEnd][colEnd]->checkMakeKing(player, rowEnd); // Check if the moved piece is eligible to become a king
    }
    return true;
}

int Checkers::getPlayerOneCaptured() const {
    return playerOneCaptured;
}

int Checkers::getPlayerTwoCaptured() const {
    return playerTwoCaptured;
}

void Checkers::updatePieces(Player player) {
    if (player == PLAYER1) {
        ++playerOneCaptured;
    } else {
        ++playerTwoCaptured;
    }
}

optional<bool> Checkers::checkWin() const {
    if(getPlayerOneCaptured() == 12) { // Player one has captured all 12 of player two's pieces
        return true;
    } else if (getPlayerTwoCaptured() == 12) { // Player two has captured all of player one's pieces
        return false;
    } else { // Neither player has captured all of the other player's pieces
        return nullopt;
    }
}

void Checkers::play(ostream &outs, istream &ins) {
    bool endGame = false;
    Player player = PLAYER1; // The current player
    createBoard();

    while (endGame == false) {
        showBoard(outs); // Show the board state after every turn
        Move move;

        // Inform whose turn it is
        if (player == PLAYER1) {
            outs << "Player 1's Turn!" << endl;
        } else {
            outs << "Player 2's Turn!" << endl;
        }

        move = getMove(player, outs, ins); // Get move from the current player
        if (tolower(move.startPos[0]) == 'q') { // Check if player wants to quit
            outs << "You forfeited" << endl;
            break;
        } else if (tolower(move.startPos[0]) == 'r') { // Check if player wants to see the rules
            showRules(outs);
            move = getMove(player, outs, ins);
        }
//        movePiece(player, move); // Perform move

        // Change whose turn it is
        if (player == PLAYER1) {
            player = PLAYER2;
        } else {
            player = PLAYER1;
        }

        if (checkWin() != nullopt) { // Check if either player has won
            endGame = true; // End the game
        }
    }
    // Print who won
    if (checkWin()) {
        outs << "Player 1 Wins!" << endl;
    } else {
        outs << "Player 2 Wins!" << endl;
    }
    outs << "Thanks for playing!";
}