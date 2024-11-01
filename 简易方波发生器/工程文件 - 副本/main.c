#include <REGX52.H>
#include "key.h"

#define MODE1 1
#define MODE2 2
#define MODE3 3

unsigned char State=3;
unsigned char Key,time_ok;
void modeshift()
{
	switch(State)
	{
		case MODE1:P2_0=0;P2_1=1;P2_2=1;break;
		case MODE2:P2_0=1;P2_1=0;P2_2=1;break;
		case MODE3:P2_0=1;P2_1=1;P2_2=0;break;
	}
}
void Timer0Init(void)		//10����@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xDC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	EA=1;
}

void main()
{
	Timer0Init();
	while(1)
	{
		if(time_ok)
		{
			time_ok=0;
			Key=key_read();
			if(Key==1)
				State=1;
			if(Key==2)
				State=2;
			if(Key==3)
				State=3;
		}
		modeshift();
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xDC;		//���ö�ʱ��ֵ
	time_ok=1;
}