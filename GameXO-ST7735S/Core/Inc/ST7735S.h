/*
 * ST7735S.h
 *
 *  Created on: Mar 4, 2025
 *      Author: Asus
 */
#include "stm32f1xx_hal.h"
#include <stdbool.h>
//#include <Stdio.h>

#ifndef INC_ST7735S_H_
#define INC_ST7735S_H_

#define ST7735S hspi1

#define DELAY 0x80

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ROTATION 0xc0

//System Function Command List
#define NOP 0x00 // khong hoat doong
#define SWRESET 0x01 // reset
#define	RDDID 0x04 // Read Display ID
#define RDDST 0x09 //Read Display Status
#define RDDPM 0x0A //Read Display Power Mode
#define RDDMADCTL 0x0B //Read Display MADCTL
#define RDDCOLMOD 0x0C //Read Display Pixel Format
#define RDDIM 0x0D //Read Display Image Mode
#define RDDSM 0x0E //Read Display Signal Mode
#define RDDSDR 0x0F //Read Display Self-Diagnostic Result
#define SLPIN 0x10 //Sleep In
#define SLPOUT 0x11 //Sleep Out
#define PTLON 0x12 //Partial Display Mode On
#define NORON 0x13 //Normal Display Mode On
#define INVOFF 0x20// Display Inversion Off
#define INVON 0x21// Display Inversion On
#define GAMSET 0x26 //Gamma Set
#define DISPOFF 0x28// Display Off
#define DISPON 0x29// Display On
#define CASET 0x2A //Column Address Set
#define RASET 0x2B// Row Address Set
#define RAMWR 0x2C// Memory Write
#define RGBSET 0x2D// Color Setting for 4K, 65K and 262K
#define RAMRD 0x2E// Memory Read
#define PTLAR 0x30// Partial Area
#define SCRLAR 0x33// Scroll Area Set
#define TEOFF 0x34// Tearing Effect Line OFF
#define TEON 0x35// Tearing Effect Line ON
#define MADCTL 0x36// Memory Data Access Control
#define VSCSAD 0x37// Vertical Scroll Start Address of RAM
#define IDMOFF 0x38// Idle Mode Off
#define IDMON 0x39// Idle Mode On
#define COLMOD 0x3A// Interface Pixel Format
#define RDID1 0xDA// Read ID1 Value
#define RDID2 0xDB// Read ID2 Value
#define RDID3 0xDC// Read ID3 Value


//Panel Function Command List
#define FRMCTR1 0xB1// Frame Rate Control (In normal mode/ Full colors)
#define FRMCTR2 0xB2// Frame Rate Control (In Idle mode/ 8-colors)
#define FRMCTR3 0xB3// Frame Rate Control (In Partial mode/ full colors)
#define INVCTR 0xB4// Display Inversion Control
#define PWCTR1 0xC0// Power Control 1
#define PWCTR2 0xC1// Power Control 2
#define PWCTR3 0xC2// Power Control 3 (in Normal mode/ Full colors)
#define PWCTR4 0xC3// Power Control 4 (in Idle mode/ 8-colors)
#define PWCTR5 0xC4// Power Control 5 (in Partial mode/ full-colors)
#define VMCTR1 0xC5// VCOM Control 1
#define VMOFCTR 0xC7// VCOM Offset Control
#define WRID2 0xD1// Write ID2 Value
#define WRID3 0xD2// Write ID3 Value
#define NVFCTR1 0xD9// NVM Control Status
#define NVFCTR2 0xDe// NVM Read Command
#define NVFCTR3 0xDF// NVM Write Command
#define GMCTRP1 0xE0// Gamma (‘+’polarity) Correction Characteristics Setting
#define GMCTRN1 0xE1// Gamma ‘-’polarity Correction Characteristics Setting
#define GCV 0xFC// Gate Pump Clock Frequency Variable

#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)


#define HEIGHT 10
#define WIDTH 7

static const uint16_t Font7x10 [] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // sp
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // !
0x2800, 0x2800, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // "
0x2400, 0x2400, 0x7C00, 0x2400, 0x4800, 0x7C00, 0x4800, 0x4800, 0x0000, 0x0000,  // #
0x3800, 0x5400, 0x5000, 0x3800, 0x1400, 0x5400, 0x5400, 0x3800, 0x1000, 0x0000,  // $
0x2000, 0x5400, 0x5800, 0x3000, 0x2800, 0x5400, 0x1400, 0x0800, 0x0000, 0x0000,  // %
0x1000, 0x2800, 0x2800, 0x1000, 0x3400, 0x4800, 0x4800, 0x3400, 0x0000, 0x0000,  // &
0x1000, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // '
0x0800, 0x1000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x1000, 0x0800,  // (
0x2000, 0x1000, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x1000, 0x2000,  // )
0x1000, 0x3800, 0x1000, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // *
0x0000, 0x0000, 0x1000, 0x1000, 0x7C00, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000,  // +
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000,  // -
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // .
0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x0000, 0x0000,  // /
0x3800, 0x4400, 0x4400, 0x5400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 0
0x1000, 0x3000, 0x5000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // 1
0x3800, 0x4400, 0x4400, 0x0400, 0x0800, 0x1000, 0x2000, 0x7C00, 0x0000, 0x0000,  // 2
0x3800, 0x4400, 0x0400, 0x1800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 3
0x0800, 0x1800, 0x2800, 0x2800, 0x4800, 0x7C00, 0x0800, 0x0800, 0x0000, 0x0000,  // 4
0x7C00, 0x4000, 0x4000, 0x7800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 5
0x3800, 0x4400, 0x4000, 0x7800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 6
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000,  // 7
0x3800, 0x4400, 0x4400, 0x3800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // 8
0x3800, 0x4400, 0x4400, 0x4400, 0x3C00, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // 9
0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,  // :
0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000,  // ;
0x0000, 0x0000, 0x0C00, 0x3000, 0x4000, 0x3000, 0x0C00, 0x0000, 0x0000, 0x0000,  // <
0x0000, 0x0000, 0x0000, 0x7C00, 0x0000, 0x7C00, 0x0000, 0x0000, 0x0000, 0x0000,  // =
0x0000, 0x0000, 0x6000, 0x1800, 0x0400, 0x1800, 0x6000, 0x0000, 0x0000, 0x0000,  // >
0x3800, 0x4400, 0x0400, 0x0800, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000,  // ?
0x3800, 0x4400, 0x4C00, 0x5400, 0x5C00, 0x4000, 0x4000, 0x3800, 0x0000, 0x0000,  // @
0x1000, 0x2800, 0x2800, 0x2800, 0x2800, 0x7C00, 0x4400, 0x4400, 0x0000, 0x0000,  // A
0x7800, 0x4400, 0x4400, 0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x0000, 0x0000,  // B
0x3800, 0x4400, 0x4000, 0x4000, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // C
0x7000, 0x4800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4800, 0x7000, 0x0000, 0x0000,  // D
0x7C00, 0x4000, 0x4000, 0x7C00, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // E
0x7C00, 0x4000, 0x4000, 0x7800, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // F
0x3800, 0x4400, 0x4000, 0x4000, 0x5C00, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // G
0x4400, 0x4400, 0x4400, 0x7C00, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // H
0x3800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3800, 0x0000, 0x0000,  // I
0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // J
0x4400, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // K
0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000,  // L
0x4400, 0x6C00, 0x6C00, 0x5400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // M
0x4400, 0x6400, 0x6400, 0x5400, 0x5400, 0x4C00, 0x4C00, 0x4400, 0x0000, 0x0000,  // N
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // O
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // P
0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x5400, 0x3800, 0x0400, 0x0000,  // Q
0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000,  // R
0x3800, 0x4400, 0x4000, 0x3000, 0x0800, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000,  // S
0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // T
0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // U
0x4400, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x1000, 0x0000, 0x0000,  // V
0x4400, 0x4400, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // W
0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000,  // X
0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // Y
0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // Z
0x1800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1800,  // [
0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x0000, 0x0000,  /* \ */
0x3000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3000,  // ]
0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ^
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFE00,  // _
0x2000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // `
0x0000, 0x0000, 0x3800, 0x4400, 0x3C00, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // a
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x0000, 0x0000,  // b
0x0000, 0x0000, 0x3800, 0x4400, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // c
0x0400, 0x0400, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // d
0x0000, 0x0000, 0x3800, 0x4400, 0x7C00, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000,  // e
0x0C00, 0x1000, 0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // f
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x7800,  // g
0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // h
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // i
0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0xE000,  // j
0x4000, 0x4000, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4400, 0x0000, 0x0000,  // k
0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000,  // l
0x0000, 0x0000, 0x7800, 0x5400, 0x5400, 0x5400, 0x5400, 0x5400, 0x0000, 0x0000,  // m
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000,  // n
0x0000, 0x0000, 0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000,  // o
0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x4000, 0x4000,  // p
0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x0400,  // q
0x0000, 0x0000, 0x5800, 0x6400, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000,  // r
0x0000, 0x0000, 0x3800, 0x4400, 0x3000, 0x0800, 0x4400, 0x3800, 0x0000, 0x0000,  // s
0x2000, 0x2000, 0x7800, 0x2000, 0x2000, 0x2000, 0x2000, 0x1800, 0x0000, 0x0000,  // t
0x0000, 0x0000, 0x4400, 0x4400, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000,  // u
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x0000, 0x0000,  // v
0x0000, 0x0000, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000,  // w
0x0000, 0x0000, 0x4400, 0x2800, 0x1000, 0x1000, 0x2800, 0x4400, 0x0000, 0x0000,  // x
0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x6000,  // y
0x0000, 0x0000, 0x7C00, 0x0800, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000,  // z
0x1800, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1800,  // {
0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,  // |
0x3000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x3000,  // }
0x0000, 0x0000, 0x0000, 0x7400, 0x4C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // ~
};

 static const uint8_t
   init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
     15,                       // 15 commands in list:
     SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
       150,                    //     150 ms delay
     SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
       255,                    //     500 ms delay
     FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
       0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
     FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
       0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
     FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
       0x01, 0x2C, 0x2D,       //     Dot inversion mode
       0x01, 0x2C, 0x2D,       //     Line inversion mode
     INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
       0x07,                   //     No inversion
     PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
       0xA2,										//
       0x02,                   //     -4.6V
       0x84,                   //     AUTO mode
     PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
       0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
     PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
       0x0A,                   //     Opamp current small
       0x00,                   //     Boost frequency
     PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
       0x8A,                   //     BCLK/2, Opamp current small & Medium low
       0x2A,  									//
     PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
       0x8A, 0xEE,							//
     VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
       0x0E,										//
     INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
     MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
     0x00,        	//     row addr/col addr, bottom to top refresh
     COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
       0x05 },                 //     16-bit color


   init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
     2,                        //  2 commands in list:
     CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
       0x00, 0x00,             //     XSTART = 0
       0x00, 0x7F,             //     XEND = 127
     RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
       0x00, 0x00,             //     XSTART = 0
       0x00, 0x9F },           //     XEND = 159

   init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
     4,                        //  4 commands in list:
    GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
       0x02, 0x1c, 0x07, 0x12,
       0x37, 0x32, 0x29, 0x2d,
       0x29, 0x25, 0x2B, 0x39,
       0x00, 0x01, 0x03, 0x10,
     GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
       0x03, 0x1d, 0x07, 0x06,
       0x2E, 0x2C, 0x29, 0x2D,
       0x2E, 0x2E, 0x37, 0x3F,
       0x00, 0x00, 0x02, 0x10,
     NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
       10,                     //     10 ms delay
     DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
       100 };                  //     100 ms delay

void St7735s_Select(void);

void St7735s_UnSelect(void);

void St7735s_CmdMode(void);

void St7735s_DataMode(void);

void St7735s_Reset(void);

void St7735s_WriteCmd (uint8_t cmd);

void St7735s_WriteData(uint8_t* Data, uint16_t size);

void St7735s_ExecuteCommandList(const uint8_t *addr);

void St7735s_WriteData8(uint8_t data);

void St7735s_WriteData16(uint16_t data);

void St7735s_Init(void);

void St7735s_SetAddressWindow(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1);

void St7735s_SetCursor(uint8_t x, uint8_t y);

void St7735s_WriteRAM_Prepare(void);

void St7735s_DisplayOFF(void);

void St7735s_DisplayON(void);

void St7735s_InvertColors(bool invert);

void St7735s_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void St7735s_WriteChar(uint16_t x, uint16_t y, char ch, const uint16_t* font, uint16_t color, uint16_t bgcolor);

void St7735s_WriteString(uint16_t x, uint16_t y, const char* str, const uint16_t* font, uint16_t color, uint16_t bgcolor);

void St7735s_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void St7735s_FillScreen(uint16_t color);

#endif /* INC_ST7735S_H_ */
