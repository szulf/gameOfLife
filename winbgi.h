// FILE: graphics.h, winbgi.h
//
// Version 3.4, December 21, 1999
//
// This is Konstantin Knizhnik's implementation of Borland's BGI graphics
// to run under Borland C++ 5.02 for Windows, with some mouse additions
// and modifications by Michael Main.
//
// The library has had many different modifications. There are many versions
// of it. For documentation and modification history please see:
//
// 		http://www.garret.ru/cpp.html
// 		http://www.cs.colorado.edu/~main/bgi/README.html
// 		http://www.cs.colorado.edu/~main/bgi/winbgim.h
//
// Some modifications by KJ, 03.06.2006 & 22.11.2017

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

// -- KJ, 22.11.2017
/*
#define far
#define huge
#define random(range) (rand() % (range))
*/

#include <windows.h>

#if !defined(CLR_INVALID)
#define CLR_INVALID 0xFFFFFFFF
#endif

// -- KJ, 03.06.2017
// Conditional color definitions to avoid collisions with conio 
#ifndef __COLORS
#define __COLORS
enum colors { 
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, 
    LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};
#endif

enum write_modes {
    COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT
};

enum line_styles {
    SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, USERBIT_LINE
};

enum fill_styles {
    EMPTY_FILL, SOLID_FILL, LINE_FILL, LTSLASH_FILL, SLASH_FILL, BKSLASH_FILL,
    LTBKSLASH_FILL, HATCH_FILL, XHATCH_FILL, INTERLEAVE_FILL, WIDE_DOT_FILL,
    CLOSE_DOT_FILL, USER_FILL
};

enum text_directions {
    HORIZ_DIR, VERT_DIR
};

enum font_types {
    DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANSSERIF_FONT, GOTHIC_FONT
};

#define LEFT_TEXT			0
#define CENTER_TEXT			1
#define RIGHT_TEXT			2
#define BOTTOM_TEXT			0
#define TOP_TEXT			2
#define NORM_WIDTH			1
#define THICK_WIDTH			3
#define DOTTEDLINE_LENGTH	2
#define CENTRELINE_LENGTH	4
#define USER_CHAR_SIZE		0
#define MAXCOLORS			15
#define CLIP_ON				1
#define CLIP_OFF			0
#define TOP_ON				1
#define TOP_OFF				0

// Definitions for the key pad extended keys are added here. I have also
// modified getch() so that when one of these keys are pressed, getch will
// return a zero followed by one of these values. This is the same way
// that it works in conio for dos applications.
// M. Main -- Nov 3, 1998
#define KEY_HOME			71
#define KEY_UP				72
#define KEY_PGUP			73
#define KEY_LEFT			75
#define KEY_CENTER			76
#define KEY_RIGHT			77
#define KEY_END				79
#define KEY_DOWN			80
#define KEY_PGDN			81
#define KEY_INSERT			82
#define KEY_DELETE			83
#define KEY_F1				59
#define KEY_F2				60
#define KEY_F3				61
#define KEY_F4				62
#define KEY_F5				63
#define KEY_F6				64
#define KEY_F7				65
#define KEY_F8				66
#define KEY_F9				67

enum graphics_errors {
   grOk = 0,
   grNoInitGraph = -1,
   grNotDetected = -2,
   grFileNotFound = -3,
   grInvalidDriver   = -4,
   grNoLoadMem = -5,
   grNoScanMem = -6,
   grNoFloodMem = -7,
   grFontNotFound = -8,
   grNoFontMem = -9,
   grInvalidMode =   -10,
   grError = -11,
   grIOerror = -12,
   grInvalidFont = -13,
   grInvalidFontNum = -14,
   grInvalidDeviceNum = -15,
   grInvalidVersion = -18
};

/* Graphics drivers constants, includes X11 which is particular to XBGI. */
#define DETECT				0
#define CGA					1
#define MCGA				2
#define EGA					3
#define EGA64				4
#define EGAMONO				5
#define IBM8514				6
#define HERCMONO			7
#define ATT400				8
#define VGA					9
#define PC3270				10

/* Graphics modes constants. */
#define CGAC0				0
#define CGAC1				1
#define CGAC2				2
#define CGAC3				3
#define CGAHI				4
#define MCGAC0				0
#define MCGAC1				1
#define MCGAC2				2
#define MCGAC3				3
#define MCGAMED				4
#define MCGAHI				5
#define EGALO				0
#define EGAHI				1
#define EGA64LO				0
#define EGA64HI				1
#define EGAMONOHI			3
#define HERCMONOHI			0
#define ATT400C0			0
#define ATT400C1			1
#define ATT400C2			2
#define ATT400C3			3
#define ATT400MED			4
#define ATT400HI			5
#define VGALO				0
#define VGAMED				1
#define VGAHI				2
#define VGAMAX				3
#define PC3270HI			0
#define IBM8514LO			0
#define IBM8514HI			1

typedef struct arccoordstype {
    int x;
    int y;
    int xstart;
    int ystart;
    int xend;
    int yend;
} arccoordstype;

typedef char fillpatterntype[8];
typedef struct fillsettingstype {
    int pattern;
    int color;
} fillsettingstype;

typedef struct linesettingstype {
    int linestyle;
    unsigned int upattern;
    int thickness;
} linesettingstype;

typedef struct palettetype {
    unsigned char size;
    signed char colors[16];
} palettetype;

typedef struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
} textsettingstype;

typedef struct viewporttype {
    int left;
    int top;
    int right;
    int bottom;
    int clip;
} viewporttype;

 // This struct was moved here to allow access to the struct (Mark Richardson 11/29/98)
struct BGIimage {
    short width;		// 2 bytes
    short height;		// 2 bytes  Note:This means bits is also aligned to 32bit(DWORD) boundry
    char  bits[1];
};

#if defined(__cplusplus)
extern "C" {
#endif

//
// Setting this variable to 0 increase speed of drawing but
// correct redraw is not possible. By default this variable is initialized by 1
//
//-- KJ, 22.11.2017 - Today computers are fast
/*
extern int bgiemu_handle_redraw;
*/
void _graphfreemem(void *ptr, unsigned int size);
void* _graphgetmem(unsigned int size);

void arc(int, int, int, int, int);
void bar(int, int, int, int);
void bar3d(int, int, int, int, int, int);
void circle(int, int, int);
void cleardevice();
void clearviewport();
void closegraph();
void detectgraph(int *, int *);
void drawpoly(int, int *);
void ellipse(int, int, int, int, int, int);
void fillellipse(int, int, int, int);
void fillpoly(int, int *);
void floodfill(int, int, int);
void getarccoords(arccoordstype *);
void getaspectratio(int *, int *);
int getbkcolor();
int getcolor();
palettetype* getdefaultpalette();
char* getdrivername();
void getfillpattern(char const *);
void getfillsettings(fillsettingstype *);
int getgraphmode();
void getimage(int, int, int, int, void *);
void getlinesettings(linesettingstype *);
int getmaxcolor();
int getmaxmode();
int getmaxx();
int getmaxy();
char* getmodename(int);
void getmoderange(int, int *, int *);
void getpalette(palettetype *);
int getpalettesize();
unsigned int getpixel(int, int);
void gettextsettings(textsettingstype *);
void getviewsettings(viewporttype *);
int getx();
int gety();
void graphdefaults();
char* grapherrormsg(int);
int graphresult();
unsigned int imagesize(int, int, int, int);
void initgraph(int *, int *, char const *);
void initwindow(int width, int height, const char* title="Windows BGI", int left=0, int top=0);
int installuserdriver(char const *, int *);
int installuserfont(char const *);
void line(int, int, int, int);
void linerel(int, int);
void lineto(int, int);
void moverel(int, int);
void moveto(int, int);
void outtext(char const *);
void outtextxy(int, int, char const *);
void pieslice(int, int, int, int, int);
void putimage(int, int, void *, int);
void putpixel(int, int, int);
void rectangle(int, int, int, int);
int registerbgidriver(void *);
int registerbgifont(void *);
void restorecrtmode();
void sector(int, int, int, int, int, int);
void setactivepage(int);
void setallpalette(palettetype *);
void setaspectratio(int, int);
void setbkcolor(int);
void setcolor(int);
void setfillpattern(char const *, int);
void setfillstyle(int, int);
unsigned int setgraphbufsize(unsigned int);
void setgraphmode(int);
void setlinestyle(int, unsigned int, int);
void setpalette(int, int);
void setrgbpalette(int, int, int, int);
void settextjustify(int, int);
void settextstyle(int, int, int);
void setusercharsize(int, int, int, int);
void setviewport(int, int, int, int, int);
void setvisualpage(int);
void setwritemode(int);
int textheight(char const *);
int textwidth(char const *);
int getch();
int kbhit();
void delay(unsigned);
void restorecrtmode();

/* Prototypes for mouse handling functions. The mousex( ) and mousey( )
*  functions return the most recent x and y coordinates detected from the
*  mouse. For the other functions, the kind parameter should be one of these:
*   WM_MOUSEMOVE       -- mouse movement
*   WM_LBUTTONDBLCLK   -- left mouse button double-click
*   WM_LBUTTONDOWN     -- left mouse button pushed down
*   WM_LBUTTONUP       -- left mouse button released up
*   WM_MBUTTONDBLCLK   -- middle mouse button double-click (might not work!)
*   WM_MBUTTONDOWN     -- middle mouse button pushed down (might not work!)
*   WM_MBUTTONUP       -- middle mouse button released up (might not work!)
*   WM_RBUTTONDBLCLK   -- right mouse button double-click
*   WM_RBUTTONDOWN     -- right mouse button pushed down
*   WM_RBUTTONUP       -- right mouse button released up
* The parameter h must be a void function with two integer parameters.
* This function will be called whenever the corresponding event occurs.
* The two integer parameters will be the x- and y-coordinates where the
* event happened.
* 
* NOTE: The middle button events aren't being caught on my Windows 95 system.
* I don't know why.
* Added by Michael Main -- 11/3/98 and 10/4/99 and 12/21/99.
*/
int mousex();
int mousey();
void registermousehandler(UINT kind, void h(int, int));
bool ismouseclick(UINT kind);
void getmouseclick(UINT kind, int& x, int& y);
void clearmouseclick(UINT kind);
    
/* Prototypes for other new functions, not in the original BGI graphics.
*  There is also a new initwindow function that can be called instead of
*  initgraph. The arguments are an explicit width and height.
*  As of 11/3, the width is now the first parameter.
*  The getactivepage() and getvisualpage() functions get the number of the
*  current active or visual page.
*/

int getactivepage();
int getvisualpage();

/* Colors can be original bgi colors (ints in the range 0...MAXCOLORS) or
*  RGB colors constructed from red, green and blue components between
*  0 and 255.
*    IS_BGI_COLOR(v): true if v is one of the original BGI colors
*    IS_RGB_COLOR(v): true if v is one of the new RGB colors
*    RED_VALUE(v) is the red value of an RGB color v
*    GREEN_VALUE(v) is the red value of an RGB color v
*    BLUE_VALUE(v) is the red value of an RGB color v
*    COLOR(r,g,b): is the rgb color formed from a red, green and blue
*                  value (all in the range 0...255).
*/

#define IS_BGI_COLOR(c) (((c) >= 0) && ((c) <= MAXCOLORS))
#define IS_RGB_COLOR(c) ((c) & 0x04000000)
#define RED_VALUE(v)   ((v) & 0xFF)
#define GREEN_VALUE(v) (((v) >> 8) & 0xFF)
#define BLUE_VALUE(v)  (((v) >> 16)& 0xFF)
#undef COLOR

// -- KJ, 22.11.2017
/*
#define COLOR(r,g,b)   (0x04000000 | RGB(r,g,b))
*/
int COLOR(int r, int g, int b);		// No longer a macro

#if defined(__cplusplus)
};
#endif

#endif

