/*
 * CommonFunc.c
 *
 *  Created on: Mar 15, 2025
 *      Author: Asus
 */


#include "CommonFunc.h"
#include <math.h>

extern uint32_t X[32];
extern uint32_t O[32];

int Button(void){
	if(HAL_GPIO_ReadPin(GPIO_CLICK_PORT, GPIO_CLICK_PIN) == 0){
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(GPIO_CLICK_PORT, GPIO_CLICK_PIN) == 0){
			while(1){
			if(HAL_GPIO_ReadPin(GPIO_CLICK_PORT, GPIO_CLICK_PIN) == 1)
			return CLICK;
			}
		}
	}
	if(HAL_GPIO_ReadPin(GPIO_UP_PORT, GPIO_UP_PIN) == 0){
			HAL_Delay(20);
			if(HAL_GPIO_ReadPin(GPIO_UP_PORT, GPIO_UP_PIN) == 0){
				while(1){
					if(HAL_GPIO_ReadPin(GPIO_UP_PORT, GPIO_UP_PIN) == 1)
					return UP;
				}
			}
		}
	if(HAL_GPIO_ReadPin(GPIO_DOWN_PORT, GPIO_DOWN_PIN) == 0){
			HAL_Delay(20);
			if(HAL_GPIO_ReadPin(GPIO_DOWN_PORT, GPIO_DOWN_PIN) == 0){
				while(1){
					if(HAL_GPIO_ReadPin(GPIO_DOWN_PORT, GPIO_DOWN_PIN) == 1)
					return DOWN;
				}
			}
		}
	if(HAL_GPIO_ReadPin(GPIO_RIGHT_PORT, GPIO_RIGHT_PIN) == 0){
			HAL_Delay(20);
			if(HAL_GPIO_ReadPin(GPIO_RIGHT_PORT, GPIO_RIGHT_PIN) == 0){
				while(1){
					if(HAL_GPIO_ReadPin(GPIO_RIGHT_PORT, GPIO_RIGHT_PIN) == 1)
					return RIGHT;
				}
			}
		}
	if(HAL_GPIO_ReadPin(GPIO_LEFT_PORT, GPIO_LEFT_PIN) == 0){
			HAL_Delay(20);
			if(HAL_GPIO_ReadPin(GPIO_LEFT_PORT, GPIO_LEFT_PIN) == 0)
				while(1){
					if(HAL_GPIO_ReadPin(GPIO_LEFT_PORT, GPIO_LEFT_PIN) == 1)
					return LEFT;
				}
		}
		return 0;
}


void BackGround(void){
	St7735s_FillScreen(ST7735_CYAN);
	St7735s_WriteString(29, 5, "CO CARO 3X3", Font7x10, ST7735_RED, ST7735_BLACK);
	St7735s_FillRectangle(4, 20, BOARD_WIDTH, BOARD_HEIGHT, ST7735_YELLOW);
}

void DrawBoard(void){
	St7735s_FillRectangle(4, 20, BOARD_WIDTH, BOARD_HEIGHT, ST7735_BLACK);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) *i), 22 +((BOARD_HEIGHT/N)*j) , 36, 36, ST7735_YELLOW);
		}
	}
}

void CreateX(uint32_t X[]) {
    X[0] = 0xC0000003;
    uint32_t a = 0xE0000000;
    uint32_t b = 0x00000007;
    for (int i = 0; i < 16; i++) {
        if (i != 0) {
            a = a >> 1;
            b = b << 1;
        }
        X[i + 1] = a | b;
    }
    for (int i = 0; i < 16; i++) {
        X[31 - i] = X[i];
    }
}

void CreateO(uint32_t O[]) {
    uint32_t a = 0x00000007;
    uint32_t b = 0xE0000000;
    uint32_t a1;
    uint32_t a2;
    for (int i = 0; i < 32; i++) {
        int c = sqrt(pow(16, 2) - pow((16 - i), 2));
        a1 = a << (16 - c);
        a2 = b >> (16 - c);
        O[i] = a1 | a2;
    }
    for (int i = 0; i < 16; i++) {
        O[31 - i] = O[i];
    }
}

void DrawXO(uint32_t X[], uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor){
    St7735s_Select();
	uint32_t i, j;
    St7735s_SetAddressWindow(x, y, x+W-1, y+H-1);
    for(i = 0; i < H; i++) {
    	uint64_t b = X[i];
        for(j = 0; j < W; j++) {
            if((b << j) & 0x80000000)  {
                uint8_t data[2] = { color >> 8, color & 0xFF };
                St7735s_WriteData(data, 2);
            } else {
                uint8_t data[2] = { bgcolor >> 8, bgcolor & 0xFF };
                St7735s_WriteData(data, 2);
            }
        }
    }
    St7735s_UnSelect();
}

void NewGame(Game* game){
	  CreateX(X);
	  CreateO(O);
	  game->cur.first = 0;
	  game->cur.second = 0;
	  for(int i = 0; i < N; i++){
		  for(int j = 0; j < N; j++){
			  game->board[i][j] = 0;
		  }
	  }
	  game->state = MENU;
	  game->player = MENU;
	  game->mode = MENU;
}

void GameMenu(void){
	BackGround();
	St7735s_WriteString(36, 40, "Hai nguoi", Font7x10, ST7735_RED, ST7735_WHITE);
	St7735s_WriteString(36, 90, "Mot nguoi", Font7x10, ST7735_RED, ST7735_BLACK);
}

void MoveCur(Game* game, int button){
	St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) * game->cur.first),
	22 + ((BOARD_HEIGHT/N) * game->cur.second), 36, 36, ST7735_YELLOW);
	switch(button){
	case UP:
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_YELLOW);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_YELLOW);
		game->cur.second = game->cur.second - 1;
		St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) * game->cur.first),
		22 + ((BOARD_HEIGHT/N) * game->cur.second), 36, 36, ST7735_WHITE);
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_WHITE);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_WHITE);
		break;
	case DOWN:
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_YELLOW);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_YELLOW);
		game->cur.second = game->cur.second + 1;
		St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) * game->cur.first),
		22 + ((BOARD_HEIGHT/N) * game->cur.second), 36, 36, ST7735_WHITE);
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_WHITE);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_WHITE);
		break;
	case RIGHT:
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_YELLOW);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_YELLOW);
		game->cur.first = game->cur.first + 1;
		St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) * game->cur.first),
		22 + ((BOARD_HEIGHT/N) * game->cur.second), 36, 36, ST7735_WHITE);
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_WHITE);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_WHITE);
		break;
	case LEFT:
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_YELLOW);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_YELLOW);
		game->cur.first = game->cur.first - 1;
		St7735s_FillRectangle(6 + ((BOARD_WIDTH/N) * game->cur.first),
		22 + ((BOARD_HEIGHT/N) * game->cur.second), 36, 36, ST7735_WHITE);
		if(game->board[game->cur.first][game->cur.second] == _X)
			DrawXO(X, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_RED, ST7735_WHITE);
		else if(game->board[game->cur.first][game->cur.second] == _O)
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->cur.first),
			24 +((BOARD_HEIGHT/N) * game->cur.second), ST7735_BLUE, ST7735_WHITE);
		break;
	default :{}
	}
}

int CheckWin(int board[N][N], pair* cur){
	// ngang
	int count = 1;
	for (int i = cur->second - 1; i >= 0; i--) {
		if (board[cur->first][i] == board[cur->first][cur->second]) count++;
		else
			break;
	}
	for (int i = cur->second + 1; i < N; i++) {
		if (board[cur->first][i] == board[cur->first][cur->second]) count++;
		else
			break;
	}
	if (count == 3) return board[cur->first][cur->second];
	// doc
	count = 1;
	for (int i = cur->first - 1; i >= 0; i--) {
		if (board[i][cur->second] == board[cur->first][cur->second]) count++;
		else
			break;
	}
	for (int i = cur->first + 1; i < N; i++) {
		if (board[i][cur->second] == board[cur->first][cur->second]) count++;
		else
			break;
	}
	if (count == 3) return board[cur->first][cur->second];
	// cheo
	count = 1;
	for (int i = cur->second - 1; i >= 0; i--) {
		if (cur->first - (cur->second - i) < 0) break;
		if (board[cur->first - (cur->second - i)][i] == board[cur->first][cur->second]) count++;
		else break;
	}
	for (int i = cur->second + 1; i < N; i++) {
		if (cur->first + (i - cur->second) >= N) break;
		if (board[cur->first + (i - cur->second)][i] == board[cur->first][cur->second]) count++;
		else break;
	}
	if (count == 3) return board[cur->first][cur->second];

	count = 1;
	for (int i = cur->second - 1; i >= 0; i--) {
		if (cur->first + (cur->second - i) >= N) break;
		if (board[cur->first + (cur->second - i)][i] == board[cur->first][cur->second]) count++;
		else break;
	}
	for (int i = cur->second + 1; i < N; i++) {
		if (cur->first - (i - cur->second) < 0) break;
		if (board[cur->first + (i - cur->second)][i] == board[cur->first][cur->second]) count++;
		else break;
	}
	if (count == 3) return board[cur->first][cur->second];
	return check_empty(board);
}

int check_empty(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == EMPTY) {
				return RUNNING;
			}
		}
	}
	return TIE;
}

int End(int x){
	if(x == RUNNING) return RUNNING;
	else if(x == X_WIN)
	  St7735s_WriteString(39, 75, "X thang", Font7x10, ST7735_RED, ST7735_CYAN);
	else if(x == O_WIN)
	  St7735s_WriteString(39, 75, "O thang", Font7x10, ST7735_BLUE, ST7735_CYAN);
	else if(x == TIE)
	  St7735s_WriteString(45, 75, "Hoa", Font7x10, ST7735_BLACK, ST7735_CYAN);
		return END;
}

void BotMove(Game* game){
	int x = game->cur.first;
	int y = game->cur.second;
	if (empty_cells(game->board) == N * N - 1) {
		if ((x < N / 2) && (y < N / 2)){
			x = x + 1;
			y = y + 1;
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * x),24 +((BOARD_HEIGHT/N) * y), ST7735_BLUE, ST7735_YELLOW);
			game->board[x][y] = _O;
		}
		else if ((x >= N / 2) && (y < N / 2)){
			x = x - 1;
			y = y + 1;
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * x),24 +((BOARD_HEIGHT/N) * y), ST7735_BLUE, ST7735_YELLOW);
			game->board[x][y] = _O;
		}
		else if ((x < N / 2) && (y >= N / 2)) {
			x = x + 1;
			y = y - 1;
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * x),24 +((BOARD_HEIGHT/N) * y), ST7735_BLUE, ST7735_YELLOW);
			game->board[x][y] = _O;
		}
		else {
			x = x - 1;
			y = y - 1;
			DrawXO(O, 8 + ((BOARD_WIDTH/N) * x),24 +((BOARD_HEIGHT/N) * y), ST7735_BLUE, ST7735_YELLOW);
			game->board[x][y] = _O;
		}
	return;
	}else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (game->board[i][j] == EMPTY) {
					game->bot_cur.first = i;
					game->bot_cur.second = j;
					game->board[i][j] = _O;
					if (CheckWin(game->board, &game->bot_cur) == O_WIN) {
						DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->bot_cur.first),
						24 +((BOARD_HEIGHT/N) * game->bot_cur.second), ST7735_BLUE, ST7735_YELLOW);
						return;
					}
					game->board[i][j] = _X;
					if (CheckWin(game->board, &game->bot_cur) == X_WIN) {
						game->board[i][j] = _O;
						DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->bot_cur.first),
						24 +((BOARD_HEIGHT/N) * game->bot_cur.second), ST7735_BLUE, ST7735_YELLOW);
						return;
					}
					game->board[i][j] = EMPTY;
				}
			}
		}
		FindBestMove(game);
		DrawXO(O, 8 + ((BOARD_WIDTH/N) * game->bot_cur.first),
		24 +((BOARD_HEIGHT/N) * game->bot_cur.second), ST7735_BLUE, ST7735_YELLOW);
		return;
	}
}

void FindBestMove(Game* game){
	game->bot_cur.first = -1;
	game->bot_cur.second = -1;
	int bestMove = -1000;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (game->board[i][j] == EMPTY) {
				game->board[i][j] = _O;
				int moveVal = minimax(game, false, -1000, 1000);
				game->board[i][j] = EMPTY;
				if (moveVal > bestMove) {
					bestMove = moveVal;
					game->bot_cur.first = i;
					game->bot_cur.second = j;
				}
			}
		}
	}
	game->board[game->bot_cur.first][game->bot_cur.second] = _O;
}

int minimax(Game* game, bool ismax, int alpha, int beta){
	int score = CheckWin(game->board, &game->bot_cur);
	if (score == X_WIN) return -1;
	if (score == O_WIN) return 1;
	if (score == TIE) return 0;
	if (ismax) {
		int best = -1000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (game->board[i][j] == EMPTY) {
					game->board[i][j] = _O;
					game->bot_cur.first = i;
					game->bot_cur.second = j;
					int a = minimax(game, false, alpha, beta);
					best = best > a ? best : a;
					game->board[i][j] = EMPTY;
					alpha = best > alpha ? best : alpha;
					if (beta <= alpha) return best;
				}
			}
		}
		return best;
	}
	else {
		int best = 10000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (game->board[i][j] == EMPTY) {
					game->board[i][j] = _X;
					game->bot_cur.first = i;
					game->bot_cur.second = j;
					int a = minimax(game, true, alpha, beta);
					best = best > a ? best : a;
					game->board[i][j] = EMPTY;
					beta = best < beta ? best : beta;
					if (beta <= alpha) return best;
				}
			}
		}
		return best;
	}
}

int empty_cells(int board[N][N]){
	int count = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(board[i][j] == EMPTY) count++;
		}
	}
	return count;
}
