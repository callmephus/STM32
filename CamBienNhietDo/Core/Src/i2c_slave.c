/*
 * i2c_slave.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Asus
 */
#include"main.h"
#include"i2c_slave.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;

#define RxSize 11
uint8_t count = 0;
uint8_t RxData[RxSize];
uint8_t I2C_Register[10];

int is_first_rx = 0 ;
int countAddr = 0;
int countrxcplt = 0;
int counterror = 0;

void process_Data(void){
	int startReg = RxData[0];
	int numReg = count - 1;
	int endReg = startReg + numReg -1;
	if(endReg > 9) Error_Handler();
	int indx = 1;

	for(int i = 0; i < numReg; i++){
		I2C_Register[startReg++] = RxData[indx++];

	}
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef* hi2c){
	HAL_I2C_EnableListen_IT(hi2c);
}
 //..........................No sequential mode............................................
//void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
//	if(TransferDirection == I2C_DIRECTION_TRANSMIT){
//		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData, RxSize, I2C_FIRST_AND_LAST_FRAME);
//	}
//	else {
//		Error_Handler();
//	}
//}
//
//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
//	count ++;
//}

//.........................Circular mode..............................................
//void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
//	if(TransferDirection == I2C_DIRECTION_TRANSMIT){
//		countAddr++;
//		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_FIRST_FRAME);
//	}
//	else {
//		Error_Handler();
//	}
//}
//
//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
//	count ++;
//	if(count >= rxSize) count = 0;
//	HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_NEXT_FRAME);
//	countrxcplt ++;
//}

// ..................Truyen du lieu biet trc so luong data...............
//void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
//	if(TransferDirection == I2C_DIRECTION_TRANSMIT){
//		if(is_first_rx == 0){
//			count = 0;
//			countAddr++;
//			HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_FIRST_FRAME);
//		}
//	}
//	else {
//		Error_Handler();
//	}
//}
//
//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
//	if(is_first_rx == 0){
//		count ++;
//		is_first_rx = 1;
//		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, RxData[0], I2C_LAST_FRAME);
//	}else {
//		count  = count +RxData[0];
//		is_first_rx = 0;
//		process_Data();
//	}
//}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
	if(TransferDirection == I2C_DIRECTION_TRANSMIT){
		countAddr++;
		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_FIRST_FRAME);
	}
	else {
		Error_Handler();
	}
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
	count ++;
	if(count < RxSize - 1){
		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_NEXT_FRAME);
	}else {
		HAL_I2C_Slave_Sequential_Receive_IT(hi2c, RxData + count, 1, I2C_LAST_FRAME);
	}
	countrxcplt ++;
	process_Data();
}
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
	counterror ++;
	HAL_I2C_EnableListen_IT(hi2c);
}

