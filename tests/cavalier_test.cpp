#include <gtest/gtest.h>

#include "exception.hpp"
#include "plateau.hpp"
#include "cavalier.hpp"
#include "pawn.hpp"

class CavalierTestBoard : public Plateau {
public:
    CavalierTestBoard() : Plateau(8, 8) {}

    void initialConditions() override {}

    void place(Piece* piece, const Position& pos) {
        addPiece(piece, pos);
    }
};

TEST(CavalierTest, ValidLMove) {
    CavalierTestBoard cb;
    cb.place(new Cavalier(true), Position("D4")); // 3,3

    EXPECT_NO_THROW(cb.play(Position("D4"), Position("E6"), true)); // 1,2
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    EXPECT_NE(cb.getPiece(Position("E6")), nullptr);
}

TEST(CavalierTest, InvalidMove) {
    CavalierTestBoard cb;
    cb.place(new Cavalier(true), Position("D4"));

    EXPECT_THROW(cb.play(Position("D4"), Position("D6"), true), InvalidMoveException); // vertical
    EXPECT_THROW(cb.play(Position("D4"), Position("F4"), true), InvalidMoveException); // horizontal
    EXPECT_THROW(cb.play(Position("D4"), Position("E5"), true), InvalidMoveException); // diagonal
}

TEST(CavalierTest, JumpOverPieces) {
    CavalierTestBoard cb;
    cb.place(new Cavalier(true), Position("D4"));
    cb.place(new Pawn(true), Position("D5"));
    cb.place(new Pawn(false), Position("E5"));

    // Cavalier can jump over pieces
    EXPECT_NO_THROW(cb.play(Position("D4"), Position("E6"), true));
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    EXPECT_NE(cb.getPiece(Position("E6")), nullptr);
}

TEST(CavalierTest, CaptureEnemyPiece) {
    CavalierTestBoard cb;
    cb.place(new Cavalier(true), Position("D4"));
    cb.place(new Pawn(false), Position("E6"));

    EXPECT_NO_THROW(cb.play(Position("D4"), Position("E6"), true));
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);
    ASSERT_NE(cb.getPiece(Position("E6")), nullptr);
    EXPECT_TRUE(cb.getPiece(Position("E6"))->getIsBlack());
}

TEST(CavalierTest, CannotCaptureOwnPiece) {
    CavalierTestBoard cb;
    cb.place(new Cavalier(true), Position("D4"));
    cb.place(new Pawn(true), Position("E6"));

    EXPECT_THROW(cb.play(Position("D4"), Position("E6"), true), InvalidMoveException);
}