#include <cstdlib>
#include <iostream>
#include <cmath>
#include "winbgi.h"
#include "living.h"

bool input = true;
int mx, my, f, n = 0;
bool ***cells;

int main(int argc, char **argv)
{
    cells = new bool**[2];
    cells[0] = new bool*[roundUp((double) HEIGHT / GRIDGAP)];
    cells[1] = new bool*[roundUp((double) HEIGHT / GRIDGAP)];	
    for (int i = 0; i < roundUp((double) HEIGHT / GRIDGAP); i++)
    {
        cells[0][i] = new bool[roundUp((double) WIDTH / GRIDGAP)];
        cells[1][i] = new bool[roundUp((double) WIDTH / GRIDGAP)];
    }
    for (int i = 0; i < roundUp((double) HEIGHT / GRIDGAP); i++)
        for (int j = 0; j < roundUp((double) WIDTH / GRIDGAP); j++)
        {
            cells[0][i][j] = false;
            cells[1][i][j] = false;
        }

    windowSetup("Game of Life");
    drawGrid();


    while (input)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            setfillstyle(SOLID_FILL, YELLOW);
            floodfill(mx, my, WHITE);
            cells[0][roundDown((double) my / GRIDGAP)][roundDown((double) mx / GRIDGAP)] = true;
        }

        if (kbhit() && (getch() == 13))
            input = false;

        // if (kbhit() && (getch() == 32))
        // {
        //     randSetup(cells[0], roundUp((double) HEIGHT / GRIDGAP), roundUp((double) WIDTH / GRIDGAP));
        //     input = false;
        // }
    }
    
    dataCopy(cells[0], cells[1], roundUp((double) HEIGHT / GRIDGAP), roundUp((double) WIDTH / GRIDGAP));
    delay(250);


    while (true)
    {
        n++;
        for (int i = 0; i < roundUp((double) HEIGHT / GRIDGAP); i++)
            for (int j = 0; j < roundUp((double) WIDTH / GRIDGAP); j++)
            {
                f = 0;
                
                if ((i != 0) && (j != 0) && (cells[0][i - 1][j - 1] == true)) f++;
                if ((i != 0) && (cells[0][i - 1][j] == true)) f++;
                if ((i != 0) && (j != (roundUp((double) WIDTH / GRIDGAP) - 1)) && (cells[0][i - 1][j + 1] == true)) f++;
                if ((i != (roundUp((double) HEIGHT / GRIDGAP) - 1)) && (j != 0) && (cells[0][i + 1][j - 1] == true)) f++;
                if ((i != (roundUp((double) HEIGHT / GRIDGAP) - 1)) && (cells[0][i + 1][j] == true)) f++;
                if ((i != (roundUp((double) HEIGHT / GRIDGAP) - 1)) && (j != (roundUp((double) WIDTH / GRIDGAP) - 1)) && (cells[0][i + 1][j + 1] == true)) f++;
                if ((j != 0) && (cells[0][i][j - 1] == true)) f++;
                if ((j != (roundUp((double) WIDTH / GRIDGAP) - 1)) && (cells[0][i][j + 1] == true)) f++;

                if ((cells[0][i][j] == true) && (f != 2) && (f != 3))
                {
                    cells[1][i][j] = false;
                    setfillstyle(SOLID_FILL, BLACK);
                    floodfill(j * GRIDGAP + 1, i * GRIDGAP + 1, WHITE);
                }

                if ((cells[0][i][j] == false) && (f == 3))
                {
                    cells[1][i][j] = true;
                    setfillstyle(SOLID_FILL, YELLOW);
                    floodfill(j * GRIDGAP + 1, i * GRIDGAP + 1, WHITE);
                }
            }

        dataCopy(cells[1], cells[0], roundUp((double) HEIGHT / GRIDGAP), roundUp((double) WIDTH / GRIDGAP));
        std::cout << n << "\n";
        
        delay(250);

        if (kbhit() && (getch() == 13))
            break;
    }


    for (int i = 0; i < roundUp((double) HEIGHT / GRIDGAP); i++)
    {
        delete cells[0][i];
        cells[0][i] = NULL;
        delete cells[1][i];
        cells[1][i] = NULL;
    }
    delete cells[0];
    cells[0] = NULL;
    delete cells[1];
    cells[1] = NULL;
    delete cells;
    cells = NULL;

    closegraph();
    return 0;
}
