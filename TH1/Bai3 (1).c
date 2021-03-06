#include "reg51.h"
//#include <at89x51.h>

//led 7-seg output data 0-9 
code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDpos=0;	//choose led 7-seg position	

unsigned char oldkey=0xff;	//push button data (release status)
unsigned char ledmode = 0;// che do hien thi led

//Define led 7-seg anot control (on/off):	
sbit LED7SEG_0 = P1^0;	//Led 7-seg 1 anot 
sbit LED7SEG_1 = P1^1;	//Led 7-seg 2 anot
sbit LED7SEG_2 = P1^2;	//Led 7-seg 3 anot
sbit LED7SEG_3 = P1^3;	//Led 7-seg 4 anot

//Buzzer (speaker) connects on P1^5 
sbit SPK  = P1^5;	//Buzzer on/off

//Define 6 push buttons on Port P3
sbit key1 = P3^7;	//Push button 1
sbit key2 = P3^6;	//Push button 2
sbit key3 = P3^5;	//Push button 3
sbit key4 = P3^4;	//Push button 4
sbit key5 = P3^3;	//Push button 5//
sbit key6 = P3^2;	//Push button 6//
			
//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}



//EXT 1 interrupt handler
void EXT1_Process(void) interrupt 2{
	EA=0;	//Cam ngat
	ledmode=ledmode+1;
	if(ledmode>3) ledmode = 0;	
	EA=1;
	delay(500);	//Cho phep ngat
}

//EXT 0 interrupt handler
void EXT0_Process(void) interrupt 0{
	EA=0;	//Cam ngat
	if(ledmode==0) ledmode = 3;
	else ledmode=ledmode-1;	
	EA=1;
	delay(500);	//Cho phep ngat
}

void delay_ms(int ms)
{
	while(ms--)
	{
		TMOD = 0x01;
		TH0 = 0xfc;
		TL0 = 0x18;
		TR0 = 1; //cho phep timer hoat dong
		while(!TF0);
		TF0 = 0; //xoa co tran
		TR0 = 0; //ngung timer 
	}
}

void hienThi(unsigned char giay)
{
	 unsigned char chuc0, donVi0, i;
	 chuc0 = giay/10; donVi0 = giay%10;

	 for(i=0;i<50;i++)
	 {
	 	LED7SEG_3 = 0; P0 = LEDfont[chuc0]; delay_ms(10); LED7SEG_2 = 1;
		LED7SEG_2 = 0; P0 = LEDfont[donVi0]; delay_ms(10); LED7SEG_3 = 1;
	 } 
}
//Chuong trinh chinh				
void main(void) 
{	
	unsigned int LEDdata=0000;		//led-7seg 4 digits data
	unsigned int giay = 0;
	SPK = 0;
	P0 = 0;			//Port 0 connect LCD
	
	while(1){					//loop forever
		//P2 = 0x55;				//8 leds on Port 2
		hienThi(giay);
		if(giay == 99){
			giay = 0;
		}
		else{
			giay++;
		}
		//displayMode(ledmode);
	}
}