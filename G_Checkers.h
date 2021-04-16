//
// Created by haz on 4/16/21.
//

#ifndef M4OEP_GRAPHICS_G_CHECKERS_H
#define M4OEP_GRAPHICS_G_CHECKERS_H

#include <optional>
#include <vector>
#include <iterator>
#include "BoardGame.h"
#include "G_Move.h"
#include "Piece.h"
using std::optional;
using std::nullopt;
using std::make_optional;
using std::istream;
using std::vector;
using std::string;

class G_Checkers {
private:
    int playerOneCaptured = 0;
    int playerTwoCaptured = 0;
    vector<vector<optional<Piece>>> board;

public:
    G_Checkers();

    void createBoard();

    vector<string> getRules() const;

    vector<vector<optional<Piece>>> getBoard() const;

    bool isPiece(int x, int y) const;

    bool validateMove(Player player, G_Move move) const;

    void movePiece(G_Move move);

};

#endif //M4OEP_GRAPHICS_G_CHECKERS_H
