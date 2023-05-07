#include"图形化界面.h"
#include<string>

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


void draw(int num_a,int num_b)
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
    // display values of num_a and num_b
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Arial"));
    TCHAR str_a[10], str_b[10];
    _stprintf_s(str_a, _T("生产者的数量: %d"), num_a);
    _stprintf_s(str_b, _T("消费者的数量: %d"), num_b);
    outtextxy(MARGIN, (ROWS + 1) * (CELL_SIZE + MARGIN), str_a);
    outtextxy( MARGIN + 5 * CELL_SIZE, (ROWS + 1) * (CELL_SIZE + MARGIN), str_b);

}


void showMessage(std::string message) {
    // clear the line first
    int y = (ROWS + 2) * (CELL_SIZE + MARGIN);
    setfillcolor(WHITE);
    solidrectangle(0, y, WINDOW_WIDTH, y + CELL_SIZE);

    // convert message to wide string
    std::wstring wmessage(message.begin(), message.end());

    // display message
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Arial"));
    int x = (WINDOW_WIDTH - textwidth(wmessage.c_str())) / 2;
    outtextxy(x, y + MARGIN, wmessage.c_str());
}

