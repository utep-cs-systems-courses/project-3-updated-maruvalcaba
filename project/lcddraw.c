/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"

signed char y = 64;
/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

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
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

/** 8x12 font - this function draws background pixels
 *  
 */
void drawChar8x12(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0xff;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 7, rrow + 11); /* relative to requested col/row */
  while (col < 12) {
    while (row < 8) {
      u_int colorBGR = (font_8x12[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      row++;
      bit >>= 1;
    }
    row = 0;
    bit = 0x80;
    col++;
  }
}

/** Draw string at col,row
 *  Type: 8x12 font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString8x12(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}

void drawDiamond(u_char offc, u_char offr, u_int color)
{
  for(u_char r = 0; r < 10; r++){
    for(u_char c = 0; c <= r; c++){            
      drawPixel(offc-c, offr+r, color);
      drawPixel(offc+c, offr+r, color);
      drawPixel(offc-c, offr+19-r, color);  /* this also makes a diamond */
      drawPixel(offc+c, offr+19-r, color);
    }
  }
}

void drawHouse(u_char offc, u_char offr, u_int color, u_int color2) /* draws a house */
{
  for(u_char r = 0; r < 10; r++){                                /* this draws the roof */
    for(u_char c = 0; c <= r; c++){            
      drawPixel(offc-c, offr+r, color);
      drawPixel(offc+c, offr+r, color);
    }
  }
  for(u_char r = 0; r < 10; r++){                                /* this draws the house */
    for(u_char c = 0; c < 7; c++){
      if(c <= 2 && r >= 6){
	drawPixel(offc-c, offr+r+10, color2);                    /* if there should be a door */
	drawPixel(offc+c, offr+r+10, color2);
      }
      else{                                                      /* else, make it like the rest */
	drawPixel(offc-c, offr+r+10, color);
	drawPixel(offc+c, offr+r+10, color);
      }
    }
  }
}


void drawRight();                        /* function is written in assembly insife drawRight.s */
/*
void drawRight()
{
  if(y < 0){                             /* checks if y is out of bounds
    y += 128;                            /* if so, move it to the correct position inbounds
  }
  for(u_char r = 30; r<40; r++){         /* these 2 loops make the main black box
    for(u_char c = 0; c<10; c++){
      signed char s = y;
      s+=c;
      if(s < 0){                         /* if new pixel position is out of bounds
	s+=128;                          /* then move it to a correct position inbounds
	drawPixel(s,r,COLOR_BLACK);
      }
      else{                              /* otherwise, was already inbounds
	drawPixel(y+c,r,COLOR_BLACK);
      }
    }
  }
  for(u_char r = 30; r<40; r++){         /* this erases the previous position of the box
    for(signed char c = 0; c<5; c++){
      signed char s = y;
      s+=c;
      s-=5;
      if(s < 0){                         /* if the new pixel position is out of bounds
	s+=128;                          /* then move it the a correct position inbounds
	drawPixel(s,r,COLOR_WHITE);
      }
      else{                              /* otherwise, was already inbounds
	drawPixel(y+c-5,r,COLOR_WHITE);
      }
    }
  }
  y+=5;                                  /* move y to the right 5 pixels
}
*/

void drawLeft()                         /* this function draws a square moving to the left */
{
  if(y < 0){                            /* checks if y is negative/out of bounds */
    y += 128;                           /* if so, changes y to the correct value inbounds */
  }
  for(u_char r = 30; r<40; r++){        /* This draws the main black box */
    for(u_char c = 0; c<10; c++){      
      signed char s = y;
      s+=c;
      if(s < 0){                        /* This checks if the position of the next pixel to be drawn is out of bounds */
	s+=128;                         /* if so, then it changes it to the correct position inbounds */
	drawPixel(s,r,COLOR_BLACK);
      }
      else{                             /* else it was already inbounds */
	drawPixel(y+c,r,COLOR_BLACK);
      }
    }
  }
  for(u_char r = 30; r<40; r++){        /* this erases the previous position of the box without erasing the new box */
    for(signed char c = 0; c<5; c++){   
      signed char s = y;
      s+=c;
      s+=10;
      if(s < 0){                        /* checks if new pixel is out of bounds */
	s+=128;                         /* if so, move it to the proper position inbounds */
	drawPixel(s,r,COLOR_WHITE);
      }
      else{                             /* else, was already inbounds */
	drawPixel(y+c+10,r,COLOR_WHITE);
      }
    }
  }
  y-=5;                                 /* move y to the left 5 pixels */
}
