#include <gtest/gtest.h>

#include <random>
#include <utility>

#include "../model/s21_maze.h"

std::pair<int, int> getRandomPairInRange(int min, int max);

TEST(MazeGeneratorTest, GenerateMazeValidDimensions) {
  int cols = 15;
  int rows = 10;
  s21::Maze maze;
  maze.GenerateMaze(cols, rows);
  EXPECT_EQ(maze.GetRows(), rows);
  EXPECT_EQ(maze.GetCols(), cols);
}

TEST(MazeGeneratorTest, GenerateMazeInvalidDimensions) {
  int rows = -1;
  int cols = 100;
  s21::Maze maze;
  EXPECT_TRUE(maze.Empty());
  maze.GenerateMaze(cols, rows);
  EXPECT_EQ(maze.GetRows(), 1);
  EXPECT_EQ(maze.GetCols(), 50);
}

TEST(MazeGeneratorTest, CheckMazeCorrectness) {
  int size = 50;
  for (int i = 0; i < 20; ++i) {
    s21::Maze maze;
    maze.GenerateMaze(size, size, time(0));
    EXPECT_EQ(maze.GetRows(), size);
    EXPECT_EQ(maze.GetCols(), size);
    for (int i = 0; i < 20; ++i) {
      std::pair<int, int> start = getRandomPairInRange(0, size - 1);
      std::pair<int, int> end = getRandomPairInRange(0, size - 1);
      std::stack<std::pair<int, int>> path = maze.FindPath(start, end);
      EXPECT_NE(path.size(), 0);
    }
  }
}

TEST(MazeGeneratorTest, SerializationDeserialization) {
  std::vector<std::vector<int>> matrix1 = {
      {0, 1, 1, 1}, {0, 1, 1, 1}, {1, 1, 0, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<int>> matrix2 = {
      {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}};
  s21::Maze maze1;
  maze1.Initialize("tests/files/correct_maze.txt");
  for (int i = 0; i < maze1.GetCols() * maze1.GetCols(); ++i) {
    EXPECT_EQ(maze1.GetRWalls()[i],
              matrix1[i / maze1.GetCols()][i % maze1.GetCols()]);
    EXPECT_EQ(maze1.GetBWalls()[i],
              matrix2[i / maze1.GetCols()][i % maze1.GetCols()]);
  }
  maze1.Save("tests/files/saved_maze.txt");
  s21::Maze maze2;
  maze2.Initialize("tests/files/saved_maze.txt");
  for (int i = 0; i < maze1.GetCols() * maze1.GetCols(); ++i) {
    EXPECT_EQ(maze1.GetRWalls()[i],
              matrix1[i / maze1.GetCols()][i % maze1.GetCols()]);
    EXPECT_EQ(maze1.GetBWalls()[i],
              matrix2[i / maze1.GetCols()][i % maze1.GetCols()]);
  }
}

std::pair<int, int> getRandomPairInRange(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  int num1 = distribution(gen);
  int num2 = distribution(gen);

  return std::make_pair(num1, num2);
}