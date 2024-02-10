#include "s21_pathfiner.h"

bool s21::PathFinder::IsCanMoveLeft() {
  bool result = true;
  if ((current.second - 1) < 0
  || visited[current.first][current.second - 1]
  || IsRightWall(current.first, current.second - 1)) result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveRight() {
  bool result = true;
  if ((current.second + 1) >= maze.GetCols()
  || visited[current.first][current.second + 1]
  || IsRightWall(current.first, current.second)) result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveUp() {
  bool result = true;
  if ((current.first - 1) < 0
  || visited[current.first - 1][current.second]
  || IsBottomWall(current.first - 1, current.second)) result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveDown() {

  bool a = IsBottomWall(current.first, current.second);
  //bool b = visited[current.first + 1][current.second];
  bool c = (current.first + 1) >= maze.GetRows();

  bool result = true;
  if ((current.first + 1) >= maze.GetRows()
  || visited[current.first + 1][current.second]
  || IsBottomWall(current.first, current.second)) result = false;
  return result;
}

bool s21::PathFinder::IsBottomWall(int r, int c)
{

}

bool s21::PathFinder::IsRightWall(int r, int c)
{

}


stack<pair<int, int>> s21::PathFinder::FindPath(pair<int, int> start, pair<int, int> end) {
  visited[start.second][start.first] = 1;
  path.push(start);
  while (!path.empty()) {
    current = path.top();
    if (current == end) {
      break;
    }
    if (IsCanMoveLeft()) {
      path.push({current.first, current.second - 1});
      visited[current.first][current.second - 1] = 1;
    }
    else if (IsCanMoveRight()) {
      path.push({current.first, current.second + 1});
      visited[current.first][current.second + 1] = 1;
    }
    else if (IsCanMoveUp()) {
      path.push({current.first - 1, current.second});
      visited[current.first - 1][current.second] = 1;
    }
    else if (IsCanMoveDown()) {
      path.push({current.first + 1, current.second});
      visited[current.first + 1][current.second] = 1;
    }
    else {
      path.pop();
    }
  }
  return path;
}
