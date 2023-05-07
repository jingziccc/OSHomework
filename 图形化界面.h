#pragma once
#include <graphics.h>
#include <conio.h>
#include<string>
void DrawCell(int row, int col, COLORREF color);
void SetCellRed(int row, int col);
void SetCellGray(int row, int col);
void draw(int num_a,int num_b);
void showMessage( std::string message);
const int ROWS = 1;
const int COLS = 20;
const int CELL_SIZE = 50;
const int MARGIN = 10;
const int WINDOW_WIDTH = COLS * CELL_SIZE + (COLS + 1) * MARGIN;
const int WINDOW_HEIGHT = (ROWS+3) * CELL_SIZE + (ROWS + 1) * MARGIN;

