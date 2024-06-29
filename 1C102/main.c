/*
    1、看门狗
    编写了看门狗相关函数。设置了初始化后最长时间才会自动复位。

    2、串口
    （1）串口1打印可行。配置了串口1接收中断。
    （2）接收数据时排除了 \r\n 。
    （3）编写串口1发送函数 USART_SendData() 。
    问题
    （1）因为内部 8M 时钟不精确，串口通信的波特率误差大于3%会导致乱码，所以只能使用外部 8M 时钟进行串口通信。
    （2）串口1中断可行，但是每次中断最多只能接收16个字节。大于16个字节后接收到的数据会乱序，字节数很多会导致只接收到第一个字节。

    3、串口0配置
    （1）设置了三个串口的相关函数。包括初始化、发送、接收和中断。
    （2）
    初始化： NS16550_init() NS16550_open()
    发送： USART_SendData() console_putstr()
    接收：只有单字符接收函数，多字符接收使用中断进行。
    中断： NS16550_interrupt_handler() NS16550_interrupt_process() NS16550_interrupt_handler_0() NS16550_interrupt_process_0()
    中断默认失能，使能配置在 NS16550_init() 函数中。
    （3）使能了串口0接收中断，实现串口0接收到数据后向串口1发送。
    串口引脚如下
            RX        TX
    串口0   GPIO6     GPIO7
    串口1   GPIO8     GPIO9
    
    4、 ESP8266 模块
    使用串口0连接 ESP8266 模块，串口1作为调试串口。
    在配置好 ESP8266 模块后，使用串口0发送函数 uart0_print() 就可以通过 ESP8266 模块 向服务端发送数据。
    在 main 函数的 for 循环当中对串口0接受数组 UART0_RX_BUF 进行判断，如果接收到字符串 on ， GPIO13 输出高，如果接收到字符串 off ， GPIO13 输出低。
    
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
    //I2C初始化
    gpio_iosel(4, 1);                       
    gpio_iosel(5, 1);
    I2C_InitTypeDef I2C_InitStruct0;
    I2C_StructInit(&I2C_InitStruct0);
    I2C_Init(&I2C_InitStruct0);
    OLED_Init();// 初始化 OLED 模块
    OLED_Clear();// OLED 清屏（就是将整个屏幕填充黑色）
    //串口初始化
    gpio_iosel(6, 1);                     
    gpio_iosel(7, 1);
    console0_init(115200);                
    console_init(9600);
    
    //IO口初始化
    gpio_init(29,1);//蜂鸣器
    gpio_init(35,1);//灯
    gpio_init(20,1);//继电器
    gpio_write(20,1);
    
    //模块进行初始化
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
