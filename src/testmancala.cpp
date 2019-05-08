#include <gtest/gtest.h>
#include "MancalaBoard.h"

TEST(MancalaBoardTest, DefaultBoardTest){
    
    CMancalaBoard Board;

    EXPECT_EQ(std::string(Board), 
                                "P1          PITS\n"
                                "      5   4   3   2   1\n"
                                "/---------------------------\\\n"
                                "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                                "| 0 |-------------------| 0 |\n"
                                "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                                "\\---------------------------/\n"
                                "      1   2   3   4   5\n"
                                "             PITS          P2\n");

    EXPECT_EQ(Board.ToString(),
                                "P1          PITS\n"
                                "      5   4   3   2   1\n"
                                "/---------------------------\\\n"
                                "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                                "| 0 |-------------------| 0 |\n"
                                "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                                "\\---------------------------/\n"
                                "      1   2   3   4   5\n"
                                "             PITS          P2\n");

    EXPECT_EQ(Board.PlayerTurn(), 0);   //Player 1 goes first -> 0 == first player

    EXPECT_EQ(Board.PlayerScore(1), 0);     //Player 1 begins with 0 stones in their store
    EXPECT_EQ(Board.PlayerScore(2), 0);     //Player 2 begins with 0 stones in their store
    EXPECT_EQ(Board.PlayerScore(3), -1);    //PlayerScore returns -1 on bad parameter 
    EXPECT_EQ(Board.PlayerScore(-3), -1);   //PlayerScore returns -1 on bad parameter 


    EXPECT_EQ(Board.PitStoneCount(1, 1), 4);    //Player 1, Pit 1 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(1, 2), 4);    //Player 1, Pit 2 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(1, 3), 4);    //Player 1, Pit 3 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(1, 4), 4);    //Player 1, Pit 4 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(1, 5), 4);    //Player 1, Pit 5 == 4 stones

    EXPECT_EQ(Board.PitStoneCount(2, 1), 4);    //Player 2, Pit 1 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(2, 2), 4);    //Player 2, Pit 2 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(2, 3), 4);    //Player 2, Pit 3 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(2, 4), 4);    //Player 2, Pit 4 == 4 stones
    EXPECT_EQ(Board.PitStoneCount(2, 5), 4);    //Player 2, Pit 5 == 4 stones

    EXPECT_EQ(Board.PitStoneCount(3, 1), -1);   //invalid parameter for player
    EXPECT_EQ(Board.PitStoneCount(-3, 1), -1);  //invalid parameter for player
    EXPECT_EQ(Board.PitStoneCount(1, 6), -1);   //invalid parameter for pit
    EXPECT_EQ(Board.PitStoneCount(3, 6), -1);   //invalid parameter for player and pit

    EXPECT_FALSE(Board.GameOver());     //game should not be over

}

TEST(MancalaBoardTest, SetBoardTest){
    CMancalaBoard DefBoard; // empty board
    int pits[MANCALA_TOTAL_PITS] = {4,4,4,4,4,4,4,4,4,4};
    int stores[MANCALA_PLAYERS] = {0,0};     
    CMancalaBoard SetBoard(1, pits, stores);    // equivalent to default board

    EXPECT_EQ(SetBoard.ToString(), DefBoard.ToString());
    EXPECT_TRUE(SetBoard.PlayerTurn() == DefBoard.PlayerTurn());
    EXPECT_FALSE(SetBoard.GameOver());

    /////// NEW BOARD ///////

    int pits2[MANCALA_TOTAL_PITS] = {0,0,0,0,0,0,0,0,0,0};
    int stores2[MANCALA_PLAYERS] = {20, 20};
    CMancalaBoard SetBoard2(2, pits2, stores2);
    EXPECT_TRUE(SetBoard2.GameOver());

    EXPECT_EQ(SetBoard2.PitStoneCount(1, 1), 0); //Player 1, Pit 1 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(1, 2), 0); //Player 1, Pit 2 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(1, 3), 0); //Player 1, Pit 3 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(1, 4), 0); //Player 1, Pit 4 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(1, 5), 0); //Player 1, Pit 5 == 0 stones

    EXPECT_EQ(SetBoard2.PitStoneCount(2, 1), 0); //Player 2, Pit 1 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(2, 2), 0); //Player 2, Pit 2 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(2, 3), 0); //Player 2, Pit 3 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(2, 4), 0); //Player 2, Pit 4 == 0 stones
    EXPECT_EQ(SetBoard2.PitStoneCount(2, 5), 0); //Player 2, Pit 5 == 0 stones

    SetBoard2.ResetBoard(); // reset board
    EXPECT_EQ(SetBoard2.ToString(), DefBoard.ToString());

    /////// NEW BOARD ///////

    int pits3[MANCALA_TOTAL_PITS] = {2, 5, -1, 7, 2, 3, -2, 1, -3, 0};
    int stores3[MANCALA_PLAYERS] = {2, -5};
    CMancalaBoard SetBoard3(2, pits3, stores3);

    EXPECT_EQ(SetBoard3.PlayerTurn(), 1);   // it should be player 2's turn = 1
    EXPECT_FALSE(SetBoard3.PlayerTurn() == DefBoard.PlayerTurn());   // DefBoard = 0, SetBoard3 = 1 
    EXPECT_FALSE(SetBoard3.GameOver());

    // it doesnt pass. it seems correct.
    std::cout << SetBoard3.ToString() << std::endl;
    EXPECT_EQ(SetBoard3.ToString(),
                                    "P1          PITS\n"
                                    "      5   4   3   2   1\n"
                                    "/---------------------------\\\n"
                                    "|   | 2 | 7 | 4 | 5 | 2 |   |\n"
                                    "| 2 |-------------------| 0 |\n"
                                    "|   | 3 | 4 | 1 | 4 | 0 |   |\n"
                                    "\\---------------------------/\n"
                                    "      1   2   3   4   5\n"
                                    "             PITS          P2\n");
}

TEST(MancalaBoardTest, ResetBoardTest){
    CMancalaBoard ResBoard;
    ResBoard.ResetBoard();

    // EXPECT_EQ(ResBoard.ToString(),
    //                             "P1          PITS\n"
    //                             "      5   4   3   2   1\n"
    //                             "/---------------------------\\\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "| 0 |-------------------| 0 |\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "\\---------------------------/\n"
    //                             "      1   2   3   4   5\n"
    //                             "             PITS          P2\n");


    // int pits[MANCALA_PIT_SLOTS];
    // int stores[MANCALA_PLAYERS];
    // CMancalaBoard SetBoard(1, pits, stores);
    // SetBoard.ResetBoard();

    // EXPECT_EQ(SetBoard.ToString(),

    //                             "P1          PITS\n"
    //                             "      5   4   3   2   1\n"
    //                             "/---------------------------\\\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "| 0 |-------------------| 0 |\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "\\---------------------------/\n"
    //                             "      1   2   3   4   5\n"
    //                             "             PITS          P2\n");

    // EXPECT_EQ(std::string(SetBoard),
    //                             "P1          PITS\n"
    //                             "      5   4   3   2   1\n"
    //                             "/---------------------------\\\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "| 0 |-------------------| 0 |\n"
    //                             "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
    //                             "\\---------------------------/\n"
    //                             "      1   2   3   4   5\n"
    //                             "             PITS          P2\n");
}

TEST(MancalaBoardTest, BasicMoveTest){
    int pits[MANCALA_PIT_SLOTS];
    int stores[MANCALA_PLAYERS];
    CMancalaBoard BasicMoveBoard(1, pits, stores);
    // we need to create the right moves to test what we want

}

TEST(MancalaBoardTest, ScoringMoveTest){
    // Needs to test that basic scoring, non double moves, non steals are correct    
}

TEST(MancalaBoardTest, DoubleMoveTest){
    // Needs to test that double move is correct
}

TEST(MancalaBoardTest, StealMoveTest){
    // Needs to test that stealing move works correctly
}

TEST(MancalaBoardTest, CantMoveTest){
    // Needs to test when player can't move correctly
}

TEST(MancalaBoardTest, BadParametersTest){
    // Needs to check that bad parameters are handled correctly
}

