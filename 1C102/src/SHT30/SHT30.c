#include <stdio.h>
#include <math.h>
//#include <rtthread.h>
#include <string.h>
#include "bsp.h"
#include "src/I2C/I2C.h"
#include "SHT30.h"
//#include "ls2k_i2c_bus.h"

//I2C写2字节命令
uint8_t i2c_write_cmd(uint16_t cmd)
{
    uint8_t cmd_buff[2];
    cmd_buff[0] = cmd>>8;
    cmd_buff[1] = cmd;
    //ls2k_i2c_send_start(busI2C2,SHT_ADDR);
    //ls2k_i2c_send_addr(busI2C2,SHT_ADDR,0);
    //i=ls2k_i2c_write_bytes(busI2C2,cmd_buff,2);
    //ls2k_i2c_send_stop(busI2C2,SHT_ADDR);

    I2C_GenerateSTART(ENABLE);  // 函数产生起始信号，表示开始传输数据。
    I2C_SendData(SHT_ADDR); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    I2C_SendData(cmd_buff[0]); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    I2C_SendData(cmd_buff[1]); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    I2C_GenerateSTOP(ENABLE);  //产生停止信号，表示传输结束

    return 0;
}

//CRC校验计算
#define CRC8_POLYNOMIAL 0x31
uint8_t CheckCrc8(uint8_t* message, uint8_t initial_value)
{
    uint8_t  remainder;
    uint8_t  i = 0, j = 0;

    remainder = initial_value;

    for(j = 0; j < 2;j++)
    {
        remainder ^= message[j];

        for (i = 0; i < 8; i++)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1)^CRC8_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return remainder;
}

//初始化代码
uint8_t sht30_init()
{
    //soft reset
    i2c_write_cmd(SOFT_RESET_CMD);
    delay_ms(50);

    return i2c_write_cmd(MEDIUM_10_CMD);//repeat medium_2
}

//read temp&humi from sensor
//1-ERR
//0-OK
uint8_t sht30_sample(float *t, float *h)
{
    uint8_t read_buff[6] = {0};

    uint16_t temp_value;
    uint16_t humi_value;
     uint16_t NumToRead=6;
    //i2c_write_cmd(READOUT_FOR_PERIODIC_MODE);//read for period mode

    I2C_GenerateSTART(ENABLE);  // 函数产生起始信号，表示开始传输数据。
    I2C_SendData(SHT_ADDR); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    I2C_SendData(0x2C); // 发送I2C设备的地址，表示要发送数据给该设备
    I2C_wait();                 //函数等待操作完成
    //I2C_SendData(0x00); // 发送I2C设备的地址，表示要发送数据给该设备
    //I2C_wait();                 //函数等待操作完成
    delay_ms(26);
    I2C_Send7bitAddress(SHT_ADDR,I2C_Direction_Receiver);
        do
         {
           I2C_ReceiveData(0,0);
           I2C_wait();
           read_buff[6-NumToRead]=I2C->DR;
           //I2C_ReceiveData(0,0);
           NumToRead--;
           //printf("NumToRead = %d\r\n", NumToRead);
         }while(NumToRead>0);
         //I2C_ReceiveData(0,0);
         //I2C_wait();
        I2C_GenerateSTOP(DISABLE);  //产生停止信号，表示传输结束
    if((CheckCrc8(read_buff, 0xFF) != read_buff[2]) && (CheckCrc8(&read_buff[3], 0xFF) != read_buff[5]))
      {
        return -1;
      }

     temp_value = ((uint16_t)read_buff[0]<<8)|read_buff[1];
    *t = -45 + 175*((float)temp_value/65535);

    humi_value = ((uint16_t)read_buff[3]<<8)|read_buff[4];
    *h = 100 * ((float)humi_value / 65535);

    return 1;
}



