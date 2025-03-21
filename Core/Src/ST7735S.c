/*
 * ST7735S.c
 *
 *  Created on: Mar 4, 2025
 *      Author: Asus
 */

#include "ST7735S.h"

extern SPI_HandleTypeDef ST7735S;

#define ST7735S_RST_PORT GPIOB
#define ST7735S_RST_PIN GPIO_PIN_0
#define ST7735S_DC_PORT GPIOB
#define ST7735S_DC_PIN GPIO_PIN_1
#define ST7735S_CS_PORT GPIOB
#define ST7735S_CS_PIN GPIO_PIN_10

void St7735s_Select(void){
	HAL_GPIO_WritePin(ST7735S_CS_PORT, ST7735S_CS_PIN, GPIO_PIN_RESET);
}

void St7735s_UnSelect(void){
	HAL_GPIO_WritePin(ST7735S_CS_PORT, ST7735S_CS_PIN, GPIO_PIN_SET);
}

void St7735s_CmdMode(void){
	HAL_GPIO_WritePin(ST7735S_DC_PORT, ST7735S_DC_PIN, GPIO_PIN_RESET);
}

void St7735s_DataMode(void){
	HAL_GPIO_WritePin(ST7735S_DC_PORT, ST7735S_DC_PIN, GPIO_PIN_SET);
}

void St7735s_Reset(void){
	HAL_GPIO_WritePin(ST7735S_RST_PORT, ST7735S_RST_PIN, GPIO_PIN_RESET); // RESET = 0
	HAL_Delay(10);
	HAL_GPIO_WritePin(ST7735S_RST_PORT, ST7735S_RST_PIN, GPIO_PIN_SET); // RESET = 1
}

void St7735s_WriteCmd(uint8_t cmd){
	St7735s_CmdMode();
	HAL_SPI_Transmit(&ST7735S, &cmd, 1, 100);
}

void St7735s_WriteData(uint8_t* Data, uint16_t size){
	St7735s_DataMode();
	HAL_SPI_Transmit(&ST7735S, Data, size, HAL_MAX_DELAY);
}

void St7735s_WriteData8(uint8_t data){
    St7735s_DataMode();
	HAL_SPI_Transmit(&ST7735S, &data, 1, 100);
}
void St7735s_WriteData16(uint16_t data){
	St7735s_DataMode();
	uint8_t data8[2];
	data8[0] = data>>8 & 0xFF;
	data8[1] = data &0xFF;
	HAL_SPI_Transmit(&ST7735S, data8, 2, 100);
}

void St7735s_ExecuteCommandList(const uint8_t *addr){
    uint8_t numCommands, numArgs;
    uint32_t ms;
    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        St7735s_WriteCmd(cmd);
        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            St7735s_WriteData((uint8_t*)addr, numArgs);
            addr += numArgs;
        }
        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            HAL_Delay(ms);
        }
    	}
}

void St7735s_Init(void){
    St7735s_Select();
    St7735s_Reset();
    St7735s_ExecuteCommandList(init_cmds1);
    St7735s_ExecuteCommandList(init_cmds2);
    St7735s_ExecuteCommandList(init_cmds3);
    St7735s_UnSelect();
}

void St7735s_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	uint8_t data[4] = {0x00, x0, 0x00, x1};
	St7735s_WriteCmd(CASET);
	St7735s_WriteData(data, 4);
	data[1] = y0;
	data[3] = y1;
	St7735s_WriteCmd(RASET);
	St7735s_WriteData(data, 4);
	St7735s_WriteCmd(RAMWR);
}

void St7735s_SetCursor(uint8_t x, uint8_t y){
	uint8_t data[2] = {0x00, x};
	St7735s_WriteCmd(CASET);
	St7735s_WriteData(data, 2);
	data[1] = y;
	St7735s_WriteCmd(RASET);
	St7735s_WriteData(data, 2);
}

void St7735s_WriteRAM_Prepare(void){
	St7735s_WriteCmd(RAMWR);
}

void St7735s_DisplayON(void){
	St7735s_Select();
	St7735s_WriteCmd(DISPON);
	HAL_Delay(10);
	St7735s_UnSelect();
}

void St7735s_DisplayOFF(void){
	St7735s_Select();
	St7735s_WriteCmd(DISPOFF);
	HAL_Delay(10);
	St7735s_UnSelect();
}

void St7735s_InvertColors(bool invert) {
    St7735s_Select();
    St7735s_WriteCmd(invert ? INVON : INVOFF);
    St7735s_UnSelect();
}

void St7735s_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;
    St7735s_Select();
    St7735s_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[2] = { color >> 8, color & 0xFF };
    St7735s_WriteData(data, 2);
    St7735s_UnSelect();
}

void St7735s_WriteChar(uint16_t x, uint16_t y, char ch, const uint16_t* font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;
    St7735s_SetAddressWindow(x, y, x+WIDTH-1, y+HEIGHT-1);
    for(i = 0; i < HEIGHT; i++) {
        b = font[(ch - 32) * HEIGHT + i];
        for(j = 0; j < WIDTH; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[2] = { color >> 8, color & 0xFF };
                St7735s_WriteData(data, 2);
            } else {
                uint8_t data[2] = { bgcolor >> 8, bgcolor & 0xFF };
                St7735s_WriteData(data, 2);
            }
        }
    }
}

void St7735s_WriteString(uint16_t x, uint16_t y, const char* str, const uint16_t* font, uint16_t color, uint16_t bgcolor){
    St7735s_Select();
    while(*str) {
        if(x + WIDTH >= ST7735_WIDTH) {
            x = 0;
            y += HEIGHT;
            if(y + HEIGHT >= ST7735_HEIGHT) {
                break;
            }
            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }
        St7735s_WriteChar(x, y, *str, font, color, bgcolor);
        x += WIDTH;
        str++;
    }
    St7735s_UnSelect();
}

void St7735s_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    St7735s_Select();
    St7735s_SetAddressWindow(x, y, x+w-1, y+h-1);

    uint8_t data[2] = { color >> 8, color & 0xFF };
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
            St7735s_WriteData(data, 2);
        }
    }
    St7735s_UnSelect();
}

void St7735s_FillScreen(uint16_t color) {
    St7735s_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}



