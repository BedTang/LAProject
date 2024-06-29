#include <stdio.h>
#include <stdbool.h>
#include "bsp.h"
#include "console.h"
#include "ls1c102_irq.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void adc_init()
{
    g_pmu->ChipCtrl |= (0x0f<<20);// 通道使能
}

int adc_read(int ch)// ch 是通道号，ch = 0 1 4 5 6 7。
{
    g_pmu->AdcCtrl = (0x01<<8) | (ch);// 设置通道 ch 开始采集。
    while(g_pmu->AdcCtrl&0x80);// 等待采集完成。 ADCCTRL->run 设为1，开启ADC转换。结束后 ADCCTRL->run 自动被置为0，表示转换完成。
    return (int)g_pmu->AdcDat;// 返回值类型 volatile unsigned int AdcDat 。一共12位。
}


