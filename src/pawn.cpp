#include "pawn.hpp"

Pawn::Pawn(bool isBlack):Piece(isBlack, "pawn") {}

bool Pawn::isValidMove(const Position &start_pos, const Position &end_pos, 
    bool isCapture, Plateau* board) const {
    (void)board;

    const int direction = getIsBlack() ? 1 : -1;
    const int dx = end_pos.getX() - start_pos.getX();
    const int dy = end_pos.getY() - start_pos.getY();
    const int startRow = getIsBlack() ? 2 : 7;

    if (isCapture) {
        return std::abs(dx) == 1 && dy == direction;
    }

    if (dx != 0) {
        return false;
    }

    if (dy == direction) {
        return true;
    }

    // first move 2 square advance from the starting row
    if (start_pos.getY() == startRow && dy == 2 * direction && firstMove == true) {
        return true;
    }

    return false;
}