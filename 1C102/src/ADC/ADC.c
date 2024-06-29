#include <stdio.h>
#include <stdbool.h>
#include "bsp.h"
#include "console.h"
#include "ls1c102_irq.h"
#include "ls1c102.h"

extern HW_PMU_t *g_pmu;

void adc_init()
{
    g_pmu->ChipCtrl |= (0x0f<<20);// ͨ��ʹ��
}

int adc_read(int ch)// ch ��ͨ���ţ�ch = 0 1 4 5 6 7��
{
    g_pmu->AdcCtrl = (0x01<<8) | (ch);// ����ͨ�� ch ��ʼ�ɼ���
    while(g_pmu->AdcCtrl&0x80);// �ȴ��ɼ���ɡ� ADCCTRL->run ��Ϊ1������ADCת���������� ADCCTRL->run �Զ�����Ϊ0����ʾת����ɡ�
    return (int)g_pmu->AdcDat;// ����ֵ���� volatile unsigned int AdcDat ��һ��12λ��
}


