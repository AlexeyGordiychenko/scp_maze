#include <gtest/gtest.h>

#include <random>
#include <utility>

#include "../model/scp_maze.h"

TEST(PathfinderTest, PathExist) {
  scp::Maze maze;
  maze.Initialize("tests/files/correct_maze.txt");
  std::pair<int, int> start = {0, 0};
  std::pair<int, int> end = {maze.GetRows() - 1, maze.GetCols() - 1};
  auto path = maze.FindPath(start, end);
  int size = path.size();
  EXPECT_NE(size, 0);
  std::stack<std::pair<int, int>> expected_path;
  expected_path.push({0, 0});
  expected_path.push({0, 1});
  expected_path.push({1, 1});
  expected_path.push({2, 1});
  expected_path.push({3, 1});
  expected_path.push({3, 2});
  expected_path.push({3, 3});
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(path.top(), expected_path.top());
    path.pop();
    expected_path.pop();
  }
}

TEST(PathfinderTest, NoPathExist) {
  scp::Maze maze;
  maze.Initialize("tests/files/broken_maze.txt");
  std::pair<int, int> start = {0, 0};
  std::pair<int, int> end = {maze.GetRows() - 1, maze.GetCols() - 1};
  auto path = maze.FindPath(start, end);
  EXPECT_EQ(path.size(), 0);
}

TEST(PathfinderTest, InValidDimensions) {
  scp::Maze maze;
  maze.Initialize("tests/files/correct_maze.txt");
  std::pair<int, int> start = {-1, -1};
  std::pair<int, int> end = {maze.GetRows() + 10, maze.GetCols() + 10};
  auto path = maze.FindPath(start, end);
  int size = path.size();
  EXPECT_NE(size, 0);
  std::stack<std::pair<int, int>> expected_path;
  expected_path.push({0, 0});
  expected_path.push({0, 1});
  expected_path.push({1, 1});
  expected_path.push({2, 1});
  expected_path.push({3, 1});
  expected_path.push({3, 2});
  expected_path.push({3, 3});
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(path.top(), expected_path.top());
    path.pop();
    expected_path.pop();
  }
}