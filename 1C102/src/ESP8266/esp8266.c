#include "esp8266.h"
#include "ls1c102.h"
#include "ns16550.h"
#include <math.h>
#include "src/GPIO/user_gpio.h"
#include <string.h>

#define WIFI_Name     B307
#define WIFI_Password oudashiniubiyyds1010
#define IP            192.168.0.111
#define Port          8080

// ESP8266 发送命令后，检测接收到的应答
// str：期待的应答结果
// 返回值：0，没有得到期待的应答结果；其他，期待应答结果的位置(str的位置)
char* esp8266_check_cmd(char *str)//
{
    char *strx = NULL;
        strx = strstr((const char*)UART0_RX_BUF, (const char*)str);
    return strx;
}

// 向 ESP8266 发送命令
// cmd：发送的命令字符串。
// ack：期待的应答结果，如果为空，则表示不需要等待应答
// waittime：等待时间
// 返回值：0，发送成功(得到了期待的应答结果)；1，发送失败
char esp8266_send_cmd(char *cmd, char *ack, uint16_t waittime)
{
    char res = 0;
    UART0_RX_STA = 0;
    uart0_print("%s\r\n", cmd);    //发送命令
    if(ack && waittime)        //需要等待应答
    {
        while(--waittime)    //等待倒计时
        {
//            delay_ms(300);
            delay_ms(100);
                if(esp8266_check_cmd(ack))
                {
                    break;//得到有效数据
                }
        }
        if(waittime == 0)
        {
            res = 1;
        }
    }
    return res;
}

// ESP8266 模块进入透传模式
void esp8266_start_trans(void)
{
    int ret = 1;

    // 设置工作模式 1：station模式   2：AP模式   3：兼容 AP+station模式
    while(esp8266_send_cmd("AT+CWMODE=1", "OK", 50));
    delay_ms(100);

    // 让 WIFI 模块重启，发送该命令后需要延时3s，等待重启结束
    uart0_print("AT+RST\r\n");
    delay_ms(1000);
    delay_ms(1000);

    // 让模块连接上自己的手机热点
    while(esp8266_send_cmd("AT+CWJAP=\"WIFI_Name\",\"WIFI_Password\"", "OK", 50));
    delay_ms(100);

    // =0：单路连接模式；=1：多路连接模式
    while(esp8266_send_cmd("AT+CIPMUX=0","OK",50));
    delay_ms(100);

    // 建立TCP连接  这三项分别代表：连接类型、远程服务器IP地址、远程服务器端口号
    while(esp8266_send_cmd("AT+CIPSTART=\"TCP\",\"IP\",Port","OK",50));

    // 是否开启透传模式，=0：表示关闭透传；=1：表示开启透传
    esp8266_send_cmd("AT+CIPMODE=1", "OK", 50);

    // 透传模式下开始发送数据的指令，这个指令之后就可以直接发数据了
    esp8266_send_cmd("AT+CIPSEND", "OK", 50);
}

// 向 ESP8266 发送数据
// cmd：发送的命令字符串
// waittime：等待时间
// 返回值：发送数据后，服务器的返回验证码
float        ppm,battery_voltage;
unsigned int current,Light_intensity;
unsigned char battery_level,temperature,humidity,
              x_acceleration,x_speed,x_displacement,//加速度，速度，位移
              y_acceleration,y_speed,y_displacement,
              z_acceleration,z_speed,z_displacement;
unsigned char current_data[8] = {0x01,0x03,0x00,0x49,0x00,0x01,0x55,0xDC},
              vibrate1   [8] = {0x02,0x04,0x01,0xA4,0x00,0x05,0x70,0x25},
              vibrate2   [8] = {0x02,0x04,0x01,0xA9,0x00,0x04,0x20,0x26};

char esp8266_send_data( char *ack1,char *ack2, uint16_t waittime)
{
    char res = 0;
    UART0_RX_STA = 0;
    //获取温湿度
    sht30_sample(&temperature,&humidity);
    //获取光照强度
    BH1750Send(0x01);
    BH1750Send(0x10);
    Light_intensity=(float)BH1750Read()/1.2;
    //获取电池电量
    battery_level=(adc_read(5)*3.3/4047*126/75-2.7)/1.5*100;
    //获取烟雾浓度
    ppm = 98.322f * pow(((3.3f - adc_read(1)*3.3/4047) / (adc_read(1)*3.3/4047) * 10/26), -1.458f);
    //获取电流，震动数据
    unsigned char i=0;
    for(i=0;i<=7;i++)
    {
        console_putch(current_data[i],1);
    }
    delay_ms(5);
        for(i=0;i<=7;i++)
    {
        console_putch(vibrate1[i],1);
    }
    delay_ms(5);
        for(i=0;i<=7;i++)
    {
        console_putch(vibrate2[i],1);
    }
    delay_ms(5);

    uart0_print("{\"id\":1,\"temperature\":%u,\"humidity\":%u,\"smoke\":%u,\"Light_intensity\":%u,\"battery_level\":%u,\"current\":%u,\"x_acceleration\":%u,\"x_speed\":%u,\"x_displacement\":%u,\"y_acceleration\":%u,\"y_speed\":%u,\"y_displacement\":%u,\"z_acceleration\":%u,\"z_speed\":%u,\"z_displacement\":%u}\r\n", (int)temperature,(int)humidity,(int)ppm,(int)Light_intensity,(int)battery_level,(int)current,(int)x_acceleration,(int)x_speed,(int)x_displacement,(int)y_acceleration,(int)y_speed,(int)y_displacement,(int)z_acceleration,(int)z_speed,(int)z_displacement);    //发送命令
    if(ppm>=100)
    {
        gpio_write(29,1);
        gpio_write(35,1);
    }
    if((current>300)|(x_acceleration>10)|(x_speed>10)|(x_displacement>10)|(y_acceleration>10)|(y_speed>10)|(y_displacement>10)|(z_acceleration>10)|(z_speed>10)|(z_displacement>10))
    {
        gpio_write(20,0);
        gpio_write(29,1);
        gpio_write(35,1);
    }
}

