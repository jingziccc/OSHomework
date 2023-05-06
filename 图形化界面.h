#pragma once
#include <graphics.h>
#include <conio.h>
void DrawCell(int row, int col, COLORREF color);
void SetCellRed(int row, int col);
void SetCellGray(int row, int col);
void draw();
const int ROWS = 1;
const int COLS = 20;
const int CELL_SIZE = 50;
const int MARGIN = 10;
const int WINDOW_WIDTH = COLS * CELL_SIZE + (COLS + 1) * MARGIN;
const int WINDOW_HEIGHT = ROWS * CELL_SIZE + (ROWS + 1) * MARGIN;