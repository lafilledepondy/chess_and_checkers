#include <gtest/gtest.h>

#include "exception.hpp"
#include "plateau.hpp"
#include "rook.hpp"
#include "pawn.hpp"

class RookTestBoard : public Plateau {
public:
    RookTestBoard() : Plateau(8, 8) {}

    void initialConditions() override {}

    void place(Piece* piece, const Position& pos) {
        addPiece(piece, pos);
    }
};

TEST(RookTest, HorizontalMoveValid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));

    EXPECT_NO_THROW(cb.play(Position("D4"), Position("H4"), true));
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    EXPECT_NE(cb.getPiece(Position("H4")), nullptr);
}

TEST(RookTest, VerticalMoveValid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));

    EXPECT_NO_THROW(cb.play(Position("D4"), Position("D8"), true));
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    EXPECT_NE(cb.getPiece(Position("D8")), nullptr);
}

TEST(RookTest, DiagonalMoveInvalid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));

    EXPECT_THROW(cb.play(Position("D4"), Position("E5"), true), InvalidMoveException);
    EXPECT_THROW(cb.play(Position("D4"), Position("F6"), true), InvalidMoveException);
}

TEST(RookTest, CannotJumpOverPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));
    cb.place(new Pawn(true), Position("D6"));

    EXPECT_THROW(cb.play(Position("D4"), Position("D8"), true), InvalidMoveException);
}

TEST(RookTest, CaptureEnemyPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));
    cb.place(new Pawn(false), Position("D8"));

    EXPECT_NO_THROW(cb.play(Position("D4"), Position("D8"), true));
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    ASSERT_NE(cb.getPiece(Position("D8")), nullptr);
    EXPECT_TRUE(cb.getPiece(Position("D8"))->getIsBlack());
}

TEST(RookTest, CannotCaptureOwnPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("D4"));
    cb.place(new Pawn(true), Position("D8"));

    EXPECT_THROW(cb.play(Position("D4"), Position("D8"), true), InvalidMoveException);
}