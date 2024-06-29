#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bsp.h"
#include "src/I2C/I2C.h"
#include "BH1750.h"
//ADDR接低电平
#define SendADDRESS 0x46
#define ReadADDRESS 0x47
//ADDR接高电平
//#define SendADDRESS 0xB8
//#define ReadADDRESS 0xB9

//寄存器地址
#define BH1750_POWER_DOWN 0x00
#define BH1750_POWER_ON 0x01
#define BH1750_RESET 0x07
#define BH1750_CON_H_RES_MODE 0x10
#define BH1750_CON_H_RES_MODE2 0x11
#define BH1750_CON_L_RES_MODE 0x13
#define BH1750_ONE_H_RES_MODE 0x20
#define BH1750_ONE_H_RES_MODE2 0x21
#define BH1750_ONE_L_RES_MODE 0x23

void BH1750Send(unsigned char Byte)
{
    I2C_GenerateSTART(ENABLE);  // 函数产生起始信号，表示开始传输数据。
    I2C_SendData(SendADDRESS); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    I2C_SendData(Byte); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();
    I2C_GenerateSTOP(DISABLE);  //产生停止信号，表示传输结束
}

unsigned int BH1750Read(void)
{
	unsigned char HighByte,LowByte;
    I2C_GenerateSTART(ENABLE);  // 函数产生起始信号，表示开始传输数据。
    I2C_SendData(ReadADDRESS); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();
    I2C_ReceiveData(0,0);
    I2C_wait();
	HighByte=I2C->DR;
    I2C_AcknowledgeConfig(DISABLE);// I2C主设备产生ack信号
    I2C_ReceiveData(0,0);
    I2C_wait();
	LowByte=I2C->DR;
    I2C_AcknowledgeConfig(ENABLE);// I2C主设备产生ack信号
    I2C_GenerateSTOP(DISABLE);  //产生停止信号，表示传输结束
	return (HighByte<<8)|LowByte;
}




