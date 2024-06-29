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

// ESP8266 ��������󣬼����յ���Ӧ��
// str���ڴ���Ӧ����
// ����ֵ��0��û�еõ��ڴ���Ӧ�������������ڴ�Ӧ������λ��(str��λ��)
char* esp8266_check_cmd(char *str)//
{
    char *strx = NULL;
        strx = strstr((const char*)UART0_RX_BUF, (const char*)str);
    return strx;
}

// �� ESP8266 ��������
// cmd�����͵������ַ�����
// ack���ڴ���Ӧ���������Ϊ�գ����ʾ����Ҫ�ȴ�Ӧ��
// waittime���ȴ�ʱ��
// ����ֵ��0�����ͳɹ�(�õ����ڴ���Ӧ����)��1������ʧ��
char esp8266_send_cmd(char *cmd, char *ack, uint16_t waittime)
{
    char res = 0;
    UART0_RX_STA = 0;
    uart0_print("%s\r\n", cmd);    //��������
    if(ack && waittime)        //��Ҫ�ȴ�Ӧ��
    {
        while(--waittime)    //�ȴ�����ʱ
        {
//            delay_ms(300);
            delay_ms(100);
                if(esp8266_check_cmd(ack))
                {
                    break;//�õ���Ч����
                }
        }
        if(waittime == 0)
        {
            res = 1;
        }
    }
    return res;
}

// ESP8266 ģ�����͸��ģʽ
void esp8266_start_trans(void)
{
    int ret = 1;

    // ���ù���ģʽ 1��stationģʽ   2��APģʽ   3������ AP+stationģʽ
    while(esp8266_send_cmd("AT+CWMODE=1", "OK", 50));
    delay_ms(100);

    // �� WIFI ģ�����������͸��������Ҫ��ʱ3s���ȴ���������
    uart0_print("AT+RST\r\n");
    delay_ms(1000);
    delay_ms(1000);

    // ��ģ���������Լ����ֻ��ȵ�
    while(esp8266_send_cmd("AT+CWJAP=\"WIFI_Name\",\"WIFI_Password\"", "OK", 50));
    delay_ms(100);

    // =0����·����ģʽ��=1����·����ģʽ
    while(esp8266_send_cmd("AT+CIPMUX=0","OK",50));
    delay_ms(100);

    // ����TCP����  ������ֱ�����������͡�Զ�̷�����IP��ַ��Զ�̷������˿ں�
    while(esp8266_send_cmd("AT+CIPSTART=\"TCP\",\"IP\",Port","OK",50));

    // �Ƿ���͸��ģʽ��=0����ʾ�ر�͸����=1����ʾ����͸��
    esp8266_send_cmd("AT+CIPMODE=1", "OK", 50);

    // ͸��ģʽ�¿�ʼ�������ݵ�ָ����ָ��֮��Ϳ���ֱ�ӷ�������
    esp8266_send_cmd("AT+CIPSEND", "OK", 50);
}

// �� ESP8266 ��������
// cmd�����͵������ַ���
// waittime���ȴ�ʱ��
// ����ֵ���������ݺ󣬷������ķ�����֤��
float        ppm,battery_voltage;
unsigned int current,Light_intensity;
unsigned char battery_level,temperature,humidity,
              x_acceleration,x_speed,x_displacement,//���ٶȣ��ٶȣ�λ��
              y_acceleration,y_speed,y_displacement,
              z_acceleration,z_speed,z_displacement;
unsigned char current_data[8] = {0x01,0x03,0x00,0x49,0x00,0x01,0x55,0xDC},
              vibrate1   [8] = {0x02,0x04,0x01,0xA4,0x00,0x05,0x70,0x25},
              vibrate2   [8] = {0x02,0x04,0x01,0xA9,0x00,0x04,0x20,0x26};

char esp8266_send_data( char *ack1,char *ack2, uint16_t waittime)
{
    char res = 0;
    UART0_RX_STA = 0;
    //��ȡ��ʪ��
    sht30_sample(&temperature,&humidity);
    //��ȡ����ǿ��
    BH1750Send(0x01);
    BH1750Send(0x10);
    Light_intensity=(float)BH1750Read()/1.2;
    //��ȡ��ص���
    battery_level=(adc_read(5)*3.3/4047*126/75-2.7)/1.5*100;
    //��ȡ����Ũ��
    ppm = 98.322f * pow(((3.3f - adc_read(1)*3.3/4047) / (adc_read(1)*3.3/4047) * 10/26), -1.458f);
    //��ȡ������������
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

    uart0_print("{\"id\":1,\"temperature\":%u,\"humidity\":%u,\"smoke\":%u,\"Light_intensity\":%u,\"battery_level\":%u,\"current\":%u,\"x_acceleration\":%u,\"x_speed\":%u,\"x_displacement\":%u,\"y_acceleration\":%u,\"y_speed\":%u,\"y_displacement\":%u,\"z_acceleration\":%u,\"z_speed\":%u,\"z_displacement\":%u}\r\n", (int)temperature,(int)humidity,(int)ppm,(int)Light_intensity,(int)battery_level,(int)current,(int)x_acceleration,(int)x_speed,(int)x_displacement,(int)y_acceleration,(int)y_speed,(int)y_displacement,(int)z_acceleration,(int)z_speed,(int)z_displacement);    //��������
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

