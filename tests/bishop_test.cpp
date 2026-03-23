#include <gtest/gtest.h>

#include "exception.hpp"
#include "plateau.hpp"
#include "bishop.hpp"
#include "pawn.hpp"

class BishopTestBoard : public Plateau {
public:
    BishopTestBoard() : Plateau(8, 8) {}

    void initialConditions() override {}

    void place(Piece* piece, const Position& pos) {
        addPiece(piece, pos);
    }
};


TEST(BishopTest, DiagonalMoveValid) {
    BishopTestBoard cb;
    cb.place(new Bishop(true), Position("A1"));

    EXPECT_NO_THROW(cb.play(Position("A1"), Position("C3"), true));
    EXPECT_EQ(cb.getPiece(Position("A1")), nullptr);
    EXPECT_NE(cb.getPiece(Position("C3")), nullptr);
}

TEST(BishopTest, DiagonalMoveInvalid) {
    BishopTestBoard cb;
    cb.place(new Bishop(true), Position("A1"));

    EXPECT_THROW(cb.play(Position("A1"), Position("A6"), false), InvalidMoveException);
    EXPECT_THROW(cb.play(Position("A1"), Position("F1"), false), InvalidMoveException);
}

TEST(BishopTest, CannotJumpOverPiece) {
    BishopTestBoard cb;
    cb.place(new Bishop(true), Position("A1"));
    cb.place(new Pawn(true), Position("B2")); // Block diagonal path

    EXPECT_THROW(cb.play(Position("A1"), Position("C3"), false), InvalidMoveException);
}

TEST(BishopTest, CaptureEnemyPiece) {
    BishopTestBoard cb;
    cb.place(new Bishop(true), Position("A1"));
    cb.place(new Pawn(false), Position("C3")); 

    EXPECT_NO_THROW(cb.play(Position("A1"), Position("C3"), true));
    EXPECT_EQ(cb.getPiece(Position("A1")), nullptr);
    ASSERT_NE(cb.getPiece(Position("C3")), nullptr);
    EXPECT_TRUE(cb.getPiece(Position("C3"))->getIsBlack()); 
}

TEST(BishopTest, CannotCaptureOwnPiece) {
    BishopTestBoard cb;
    cb.place(new Bishop(true), Position("A1"));
    cb.place(new Pawn(true), Position("C3")); 

    EXPECT_THROW(cb.play(Position("A1"), Position("C3"), true), InvalidMoveException);
}