#include <algorithm>

#include "s21_labyrinth_tests.h"

TEST_F(CaveTestCase, 0) {
  s21::Cave cave;
  cave.GenerateCave(50, 10, 10, kRndSeed);
  auto result = std::vector<bool>{
      0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0,
      1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0,
      0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1};
  EXPECT_TRUE(cave.GetRows() == 10);
  EXPECT_TRUE(cave.GetCols() == 10);
}

TEST_F(CaveTestCase, 1) {
  s21::Cave cave;
  cave.GenerateCave(100, 20, 30, kRndSeed);
  auto cells = cave.GetCells();
  EXPECT_EQ(std::count(cells.begin(), cells.end(), true), 20 * 30);
  EXPECT_TRUE(cave.GetRows() == 20);
  EXPECT_TRUE(cave.GetCols() == 30);
}

TEST_F(CaveTestCase, 2) {
  s21::Cave cave;
  cave.GenerateCave(0, 40, 1, kRndSeed);
  auto cells = cave.GetCells();
  EXPECT_EQ(std::count(cells.begin(), cells.end(), true), 0);
  EXPECT_TRUE(cave.GetRows() == 40);
  EXPECT_TRUE(cave.GetCols() == 1);
}

TEST_F(CaveTestCase, 3) {
  s21::Cave cave;
  cave.GenerateCave(10, -5, 10, kRndSeed);
  EXPECT_TRUE(cave.Empty());
  EXPECT_TRUE(cave.GetRows() == 0);
  EXPECT_TRUE(cave.GetCols() == 10);
}

TEST_F(CaveTestCase, 4) {
  s21::Cave cave;
  cave.GenerateCave(70, 6, -2, kRndSeed);
  EXPECT_TRUE(cave.Empty());
  EXPECT_TRUE(cave.GetRows() == 6);
  EXPECT_TRUE(cave.GetCols() == 0);
}

TEST_F(CaveTestCase, 5) {
  s21::Cave cave;
  cave.GenerateCave(70, -10, -20, kRndSeed);
  EXPECT_TRUE(cave.Empty());
  EXPECT_TRUE(cave.GetRows() == 0);
  EXPECT_TRUE(cave.GetCols() == 0);
}

TEST_F(CaveTestCase, 6) {
  s21::Cave cave;
  cave.GenerateCave(120, 10, 10, kRndSeed);
  auto cells = cave.GetCells();
  EXPECT_EQ(std::count(cells.begin(), cells.end(), true), 10 * 10);
  EXPECT_TRUE(cave.GetRows() == 10);
  EXPECT_TRUE(cave.GetCols() == 10);
}

TEST_F(CaveTestCase, 7) {
  s21::Cave cave;
  cave.GenerateCave(-50, 5, 5, kRndSeed);
  auto cells = cave.GetCells();
  EXPECT_EQ(std::count(cells.begin(), cells.end(), true), 0);
  EXPECT_TRUE(cave.GetRows() == 5);
  EXPECT_TRUE(cave.GetCols() == 5);
}

TEST_F(CaveTestCase, 8) {
  s21::Cave cave_init;
  cave_init.Initialize("tests/files/cave_1_init.txt");
  s21::Cave cave_res;
  cave_res.Initialize("tests/files/cave_1_res.txt");
  TestCaveAlgorithm(cave_init, cave_res, 4, 3, 6);
}

TEST_F(CaveTestCase, 9) {
  s21::Cave cave_init;
  cave_init.Initialize("tests/files/cave_2_init.txt");
  s21::Cave cave_res;
  cave_res.Initialize("tests/files/cave_2_res.txt");
  TestCaveAlgorithm(cave_init, cave_res, 6, 1, 4);
}

TEST_F(CaveTestCase, 10) {
  s21::Cave cave_init;
  cave_init.Initialize("tests/files/cave_3_init.txt");
  s21::Cave cave_res;
  cave_res.Initialize("tests/files/cave_3_res.txt");
  TestCaveAlgorithm(cave_init, cave_res, 2, 5, 19);
}
