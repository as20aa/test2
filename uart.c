#include "uart.h"

void init_uart(void)
{
	TMOD=0x21;				
	TH1=0xfd;				
	TL1=0xfd;		
		
	SCON=0x50;
	PS=1;      //串口中断设为高优先级别
	TR0=1;	   //启动定时器			
	TR1=1;
	ET0=1;     //打开定时器0中断			
	ES=1;	
	EA=1;
}
void  SeriPushSend(unsigned char send_data)
{
    SBUF=send_data;  
	while(!TI);TI=0;	  
}

