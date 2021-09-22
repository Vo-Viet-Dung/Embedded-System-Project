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

void display(unsigned int da)
{
	P0=0xFF;			//Port 0 data off
	da=da%10000;	 	//output data for led 7-seg (4-digits)
	switch(LEDpos){
	case 0:		//choose led 7-seg 1
		LED7SEG_0=0;
		LED7SEG_1=1;	
		LED7SEG_2=1;		
		LED7SEG_3=1;
		P0=LEDfont[da/1000];	//Chu so hang nghin
		break;
	case 1:		//choose led 7-seg 2
		LED7SEG_0=1;
		LED7SEG_1=0;	
		LED7SEG_2=1;		
		LED7SEG_3=1;
		P0=LEDfont[da%1000/100]; //Chu so hang tram
		break;
	case 2:		//choose led 7-seg 3
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=0;		
		LED7SEG_3=1;
		P0=LEDfont[da%100/10];  //Chu so hang chuc
		break;
	case 3:		//choose led 7-seg 4
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=1;		
		LED7SEG_3=0;
		P0=LEDfont[da%10];	 //Chu so hang don vi
		break;
	}
	LEDpos++;		//turn around
	if(LEDpos>3)
		LEDpos=0;	
}
//Read buttons 1-> 6 on P3
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//if any buttons pressed

		SPK=1;				//turn on buzzer

		delay(10);			//delay for buzzer pulse
		if(oldkey!=(P3&0xfc)){//if any buttons pressed
			oldkey=P3&0xfc;		//update buttons values		
			if(key1==0)
				lkey=1;		//press button 1
			else if(key2==0)
				lkey=2;		//press button 2
			else if(key3==0)
				lkey=3;		//press button 3
			else if(key4==0)
				lkey=4;		//press button 4
			else if(key5==0)
				lkey=5;		//press button 5
			else if(key6==0)
				lkey=6;		//press button 6
		}
	}
	else{
		oldkey=0xfc;		//default data of buttons port

		SPK=0;				//turn off buzzer
	}
	return lkey;
}

// hien thi led	theo cac che do
void displayLed(unsigned char mode)	 //n la so lan chay moi
{
	switch(mode)
	{
	case 0: //che do 1
		P2 = 0xff;//tat tat ca cac den
		delay(10000);
		P2 = 0; //bat tat ca cac den
		delay(10000);
		break;
	case 1: //che do 2 hien thi lan luot cac led tu phai qua trai
		P2= 0xff;
		delay(10000);
		P2=0xfe;
		delay(10000);
		P2=0xfd;
		delay(10000);
		P2=0xfb;
		delay(10000);
		P2=0xf7;
		delay(10000);
		P2=0xef;
		delay(10000);
		P2=0xdf;
		delay(10000);
		P2=0xbf;
		delay(10000);
		P2=0x7f;
		delay(10000);	
		break;
	case 2: //che do 3 	hien thi lan luot cac led tu trai qua phai
		P2 = 0xff;
		delay(10000);
		P2=0x7f;
		delay(10000);
		P2=0xbf;
		delay(10000);
		P2=0xdf;
		delay(10000);
		P2=0xef;
		delay(10000);
		P2=0xf7;
		delay(10000);
		P2=0xfb;
		delay(10000);
		P2=0xfd;
		delay(10000);
		P2=0xfe;
		delay(10000);
		break;
	case 3: //
		P2 = 0xff;
		delay(10000);
		P2 = 0x7e;
		delay(10000);
		P2 = 0xbd;
		delay(10000);
		P2 = 0xdb;
		delay(10000);
		P2 = 0xe7;
		delay(10000);
		P2 = 0xdb;
		delay(10000);
		P2 = 0xbd;
		delay(10000);
		P2 = 0x7e;
		delay(10000);
		break;
	}

}

//EXT 1 interrupt handler
void EXT1_Process() interrupt 2{
	EA=0;	//Cam ngat
	ledmode=ledmode+1;
	if(ledmode>3) {
	ledmode = 0;
	}	
	EA=1;	//Cho phep ngat
}

//EXT 0 interrupt handler
void EXT0_Process() interrupt 0{
	EA=0;	//Cam ngat
	if(ledmode==0) {
	ledmode = 3;
	}
	else ledmode=ledmode-1;	
	EA=1;	//Cho phep ngat
}

// init()
void init(){
	key5 = 1; // thiet lap P3^3 la chan vao
	key6 = 1; // thiet lap p3^2 la chan vao
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;
	EA=1;

}
//Chuong trinh chinh				
void main(void) 
{		//led-7seg 4 digits data 
	unsigned char i;
	unsigned char j;
	SPK = 0;
	
	while(1){					//loop forever
		for(i = 0;i<4;i++)
	{
		for(j = 0;j<5;j++)
		{
		displayLed(i);
		delay(10000);
		}
	}		//display 4 digits led 7-seg
		delay(100);
	}
}
