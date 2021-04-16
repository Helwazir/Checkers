//
// Created by haz on 4/16/21.
//

#ifndef M4OEP_GRAPHICS_CHECKERS_H
#define M4OEP_GRAPHICS_CHECKERS_H

#include <optional>
#include <vector>
#include <iterator>

#include "G_Move.h"
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
    Checkers();

    void createBoard();

    vector<string> getRules() const;

    vector<vector<optional<Piece>>> getBoard() const;

    bool validateMove(Player player, G_Move move) const;

    void movePiece(G_Move move);

    bool checkWin() const;

    string getResults() const;

};

#endif //M4OEP_GRAPHICS_CHECKERS_H
