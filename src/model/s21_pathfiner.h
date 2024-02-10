#include <vector>
#include <utility>
#include <stack>
#include "s21_maze.h"

using namespace std;

namespace s21 {

class PathFinder
{
private:
  bool IsCanMoveLeft();
  bool IsCanMoveRight();
  bool IsCanMoveUp();
  bool IsCanMoveDown();
  bool IsBottomWall(int r, int c);
  bool IsRightWall(int r, int c);

  stack<pair<int, int>> path;
  pair<int, int> current;
  Maze maze;
  std::vector<std::vector<int>> visited;
public:
  std::stack<pair<int, int>> FindPath(pair<int, int> start, pair<int, int> end);
  //PathFinder(Maze& maze) : maze(maze), visited(maze.GetHeight(), std::vector<int>(maze.GetWidth(), 0)) {
    //std::vector<std::vector<int>> visited(maze.GetHeight(), std::vector<int>(maze.GetWidth(), 0));
  //}
};
}
