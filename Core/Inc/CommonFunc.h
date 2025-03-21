/*
 * CommonFunc.h
 *
 *  Created on: Mar 15, 2025
 *      Author: Asus
 */
#include "stm32f1xx_hal.h"
#include "ST7735S.h"

#ifndef INC_COMMONFUNC_H_
#define INC_COMMONFUNC_H_

// define players
#define EMPTY 0
#define _X 1
#define _O 2
#define N 3
// define game states
#define RUNNING 0
#define X_WIN 1
#define O_WIN 2
#define TIE 3
#define MENU 4
#define END 5
// define choices
#define TWO_PLAYER 1
#define ONE_PLAYER 2

#define BOARD_WIDTH 120
#define BOARD_HEIGHT 120
#define W 32
#define H 32

#define CLICK 1
#define UP 2
#define DOWN 3
#define RIGHT 4
#define LEFT 5

#define GPIO_CLICK_PORT GPIOB
#define GPIO_CLICK_PIN GPIO_PIN_7
#define GPIO_UP_PORT GPIOB
#define GPIO_UP_PIN GPIO_PIN_6
#define GPIO_DOWN_PORT GPIOB
#define GPIO_DOWN_PIN GPIO_PIN_5
#define GPIO_RIGHT_PORT GPIOB
#define GPIO_RIGHT_PIN GPIO_PIN_4
#define GPIO_LEFT_PORT GPIOB
#define GPIO_LEFT_PIN GPIO_PIN_3

typedef struct {
    int first;
    int second;
} pair;

typedef struct {
    int board[N][N];
    int player;
    int state;
    int mode;
    pair cur;
    pair bot_cur;
}Game;

int Button(void);

void BackGround(void);

void DrawBoard(void);

void CreateX( uint32_t X[]);

void CreateO(uint32_t O[]);

void DrawXO(uint32_t X[], uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor);

void NewGame(Game* game);

void GameMenu(void);

void MoveCur(Game* game, int button);

int CheckWin(int board[N][N], pair* cur);

int check_empty(int board[N][N]);

void BotMove(Game* game);

int empty_cells(int board[N][N]);

int End(int x);

void FindBestMove(Game* game);

int minimax(Game* game, bool ismax, int alpha, int beta);

#endif /* INC_COMMONFUNC_H_ */
