/*
    1�����Ź�
    ��д�˿��Ź���غ����������˳�ʼ�����ʱ��Ż��Զ���λ��

    2������
    ��1������1��ӡ���С������˴���1�����жϡ�
    ��2����������ʱ�ų��� \r\n ��
    ��3����д����1���ͺ��� USART_SendData() ��
    ����
    ��1����Ϊ�ڲ� 8M ʱ�Ӳ���ȷ������ͨ�ŵĲ�����������3%�ᵼ�����룬����ֻ��ʹ���ⲿ 8M ʱ�ӽ��д���ͨ�š�
    ��2������1�жϿ��У�����ÿ���ж����ֻ�ܽ���16���ֽڡ�����16���ֽں���յ������ݻ������ֽ����ܶ�ᵼ��ֻ���յ���һ���ֽڡ�

    3������0����
    ��1���������������ڵ���غ�����������ʼ�������͡����պ��жϡ�
    ��2��
    ��ʼ���� NS16550_init() NS16550_open()
    ���ͣ� USART_SendData() console_putstr()
    ���գ�ֻ�е��ַ����պ��������ַ�����ʹ���жϽ��С�
    �жϣ� NS16550_interrupt_handler() NS16550_interrupt_process() NS16550_interrupt_handler_0() NS16550_interrupt_process_0()
    �ж�Ĭ��ʧ�ܣ�ʹ�������� NS16550_init() �����С�
    ��3��ʹ���˴���0�����жϣ�ʵ�ִ���0���յ����ݺ��򴮿�1���͡�
    ������������
            RX        TX
    ����0   GPIO6     GPIO7
    ����1   GPIO8     GPIO9
    
    4�� ESP8266 ģ��
    ʹ�ô���0���� ESP8266 ģ�飬����1��Ϊ���Դ��ڡ�
    �����ú� ESP8266 ģ���ʹ�ô���0���ͺ��� uart0_print() �Ϳ���ͨ�� ESP8266 ģ�� �����˷������ݡ�
    �� main ������ for ѭ�����жԴ���0�������� UART0_RX_BUF �����жϣ�������յ��ַ��� on �� GPIO13 ����ߣ�������յ��ַ��� off �� GPIO13 ����͡�
    
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "bsp.h"
#include "console.h"
#include "ls1c102.h"
#include "ns16550.h"

#include "src/GPIO/user_gpio.h"
#include "src/WDG/ls1x_wdg.h"
#include "src/ESP8266/esp8266.h"
#include "src/ADC/ADC.h"
#include "src/SHT30/SHT30.h"
#include "src/I2C/I2C.h"
#include "src/OLED/oled.h"
extern HW_PMU_t *g_pmu;
extern int printk(const char* format, ...);
extern int uart0_print(const char* format, ...);

void main(void)
{
    WdgInit();
    //I2C��ʼ��
    gpio_iosel(4, 1);                       
    gpio_iosel(5, 1);
    I2C_InitTypeDef I2C_InitStruct0;
    I2C_StructInit(&I2C_InitStruct0);
    I2C_Init(&I2C_InitStruct0);
    OLED_Init();// ��ʼ�� OLED ģ��
    OLED_Clear();// OLED ���������ǽ�������Ļ����ɫ��
    //���ڳ�ʼ��
    gpio_iosel(6, 1);                     
    gpio_iosel(7, 1);
    console0_init(115200);                
    console_init(9600);
    
    //IO�ڳ�ʼ��
    gpio_init(29,1);//������
    gpio_init(35,1);//��
    gpio_init(20,1);//�̵���
    gpio_write(20,1);
    
    //ģ����г�ʼ��
    adc_init();                             
    sht30_init();
 //   esp8266_start_trans();
                OLED_ShowCHinese(0, 0, 0);
            OLED_ShowCHinese(16, 0, 12);
            OLED_ShowCHinese(0, 3, 1);
            OLED_ShowCHinese(16, 3, 12);
            OLED_ShowCHinese(0, 6, 7);
            OLED_ShowCHinese(16, 6, 8);
            OLED_ShowCHinese(32, 6, 9);
            OLED_ShowCHinese(48, 6, 12);
    for (;;)
    {
        esp8266_send_data("OK", "ERROR",50);
    }
}
