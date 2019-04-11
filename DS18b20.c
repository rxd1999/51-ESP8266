#include "DS18B20.h"
#include <intrins.h>
sfr P3 = 0xB0;
sbit DQ=P3^7;

int outTemp()
{
	int t=0;
	t=TempRead();
	t=(int)(t*0.0625+0.5);
	return t;

}
void Init()
{
	DQ=0;
	delay_10um(50);
	DQ=1;
	delay_10um(10);
	DQ=1;
}
int TempRead()
{
	unsigned char High;
	unsigned char Low;
	unsigned int temp=0;
	Init();
	delay_ms(1);
	WriteByte(0xcc);
	WriteByte(0x44);
	delay_ms(100);
	Init();
	delay_ms(1);
	WriteByte(0xcc);
	WriteByte(0xbe);
	Low=ReadByte();
	High=ReadByte();
	temp=High;
	temp=(temp<<8)|Low;
	return temp;
}
void WriteByte(unsigned char dat)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		DQ=0;
		_nop_();
		DQ=dat&0x01;
		delay_10um(6);
		DQ=1;
		_nop_();
		dat>>=1;
	}
}
unsigned char ReadByte(void)
{
	unsigned char j;
	unsigned char Byte=0x00;
	unsigned char bits=0x00;
	for(j=0;j<8;j++)
	{
		DQ=0;
		_nop_();
		DQ=1;
		delay_10um(1);
		bits=DQ;
		Byte=(Byte>>1)|(bits<<7);
		delay_10um(5);
	}
	return Byte;
}
void delay_ms(unsigned int n)
{
    unsigned int i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<123;j++);
}
//微秒延时
void delay_10um(unsigned int n)
{
    while(n--);
}