#ifndef _living_h
#define _living_h

#define WIDTH 512
#define HEIGHT 512
#define GRIDGAP 20
#define roundUp(num) (int) ceil(num)
#define roundDown(num) (int) floor(num)

void windowSetup(const char*, int = WIDTH, int = HEIGHT, int = BLACK, int = WHITE);
void drawGrid(int = WIDTH, int = HEIGHT, int = GRIDGAP);
void dataCopy(bool**, bool**, int, int);
void randSetup(bool**, int, int);

#endif
