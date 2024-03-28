#pragma once
#include "board.h"


class ai: public board{
int x, y;
int depth;

public:
ai(int depth_limit):depth(depth_limit){};
int minimax(board board, int depth, int alpha, int beta, bool player);
void move(board board);
int getx() const { return x; }
int gety() const { return y; }
};