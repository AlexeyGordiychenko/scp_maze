#ifndef S21_MAZE_LABYRINTH_TESTS_H
#define S21_MAZE_LABYRINTH_TESTS_H

#include <gtest/gtest.h>

#include "../model/s21_cave.h"

class CaveTestCase : public ::testing::Test {
 protected:
  int kRndSeed = 42;
  void TestCaveAlgorithm(s21::Cave& cave_init, s21::Cave& cave_res,
                         int birth_limit, int death_limit, int steps) {
    int count = 0;
    while (cave_init.CellularAutomaton(birth_limit, death_limit)) {
      ++count;
    }
    EXPECT_EQ(count, steps);
    EXPECT_EQ(cave_init.GetRows(), cave_res.GetRows());
    EXPECT_EQ(cave_init.GetCols(), cave_res.GetCols());
    EXPECT_EQ(cave_init.GetCells(), cave_res.GetCells());
  }
};

#endif  // S21_MAZE_LABYRINTH_TESTS_H
