#include <cstdlib>
#include <iostream>
#include <time.h>
#include "winbgi.h"
#include "living.h"

void windowSetup(const char* n, int w, int h, int bgC, int c)
{
    srand((unsigned) time(NULL));
    initwindow(w, h, n);
    setbkcolor(bgC);
    setcolor(c);
    cleardevice();
}

void drawGrid(int w, int h, int g)
{
    for (int i = 0; i < w; i += g)
        line(i, 0, i, h);

    for (int i = 0; i < h; i += g)
        line(0, i, w, i);
}

void dataCopy(bool **src, bool **dest, int s1, int s2)
{
    for (int i = 0; i < s1; i++)
        for (int j = 0; j < s2; j++)
            dest[i][j] = src[i][j];
}

void randSetup(bool** arr, int s1, int s2)
{
    for (int i = 0; i < s1; i++)
        for (int j = 0; j < s2; j++)
        {
            arr[i][j] = rand() % 2;
            setfillstyle(SOLID_FILL, YELLOW);
            if (arr[i][j])
                floodfill(j * GRIDGAP + (GRIDGAP / 2), i * GRIDGAP + (GRIDGAP / 2), WHITE);
        }
}
