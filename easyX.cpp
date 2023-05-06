#include"图形化界面.h"


void DrawCell(int row, int col, COLORREF color)
{
    int left = (col - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int top = (row - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillcolor(color);
    solidrectangle(left, top, right, bottom);
}
void SetCellRed(int row, int col)
{
    int left = (col - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int top = (row - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillcolor(RED);
    solidrectangle(left, top, right, bottom);
}

void SetCellGray(int row, int col)
{
    int left = (col - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int top = (row - 1) * (CELL_SIZE + MARGIN) + MARGIN;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillcolor(LIGHTGRAY);
    solidrectangle(left, top, right, bottom);
}


void draw()
{
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(WHITE);
    cleardevice();

    // draw cells
    for (int row = 1; row <= ROWS; row++)
    {
        for (int col = 1; col <= COLS; col++)
        {
            DrawCell(row, col, LIGHTGRAY);
        }
    }


}