/** \file lcddraw.h
 *  \brief Adapted from RobG's EduKit
 */

#ifndef lcddraw_included
#define lcddraw_included

typedef unsigned int u_int;
typedef unsigned char u_char;

extern signed char y;

/** Draw single pixel at col, row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR);

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR);

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR);

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string, 
		   u_int fgColorBGR, u_int bgColorBGR);

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char col, u_char row, char c, 
		 u_int fgColorBGR, u_int bgColorBGR);

/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR);


/** Draw string at col,row
 *  Type: 8x12 Font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString8x12(u_char col, u_char row, char *string, 
		   u_int fgColorBGR, u_int bgColorBGR);

/** 8x12 font - this function draws background pixels
 */
void drawChar8x12(u_char col, u_char row, char c, 
		 u_int fgColorBGR, u_int bgColorBGR);

/* This function draws a diamond.
 */
void drawDiamond(u_char offc, u_char offr, u_int color);

/*
  this function draws a box that moves to the right
 */
void drawRight();

/*
  this function draws a box that moves to the left
 */
void drawLeft();

/*
  this function draws a small house.
 */
void drawHouse(u_char offc, u_char offr, u_int color, u_int color2);
#endif // included

