#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bsp.h"
#include "src/I2C/I2C.h"
#include "BH1750.h"
//ADDR�ӵ͵�ƽ
#define SendADDRESS 0x46
#define ReadADDRESS 0x47
//ADDR�Ӹߵ�ƽ
//#define SendADDRESS 0xB8
//#define ReadADDRESS 0xB9

//�Ĵ�����ַ
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
    I2C_GenerateSTART(ENABLE);  // ����������ʼ�źţ���ʾ��ʼ�������ݡ�
    I2C_SendData(SendADDRESS); // ����I2C�豸�ĵ�ַ����ʾҪ�������ݸ����豸
    I2C_wait();                 //�����ȴ��������
    I2C_SendData(Byte); // ����I2C�豸�ĵ�ַ����ʾҪ�������ݸ����豸
    I2C_wait();
    I2C_GenerateSTOP(DISABLE);  //����ֹͣ�źţ���ʾ�������
}

unsigned int BH1750Read(void)
{
	unsigned char HighByte,LowByte;
    I2C_GenerateSTART(ENABLE);  // ����������ʼ�źţ���ʾ��ʼ�������ݡ�
    I2C_SendData(ReadADDRESS); // ����I2C�豸�ĵ�ַ����ʾҪ�������ݸ����豸
    I2C_wait();
    I2C_ReceiveData(0,0);
    I2C_wait();
	HighByte=I2C->DR;
    I2C_AcknowledgeConfig(DISABLE);// I2C���豸����ack�ź�
    I2C_ReceiveData(0,0);
    I2C_wait();
	LowByte=I2C->DR;
    I2C_AcknowledgeConfig(ENABLE);// I2C���豸����ack�ź�
    I2C_GenerateSTOP(DISABLE);  //����ֹͣ�źţ���ʾ�������
	return (HighByte<<8)|LowByte;
}




