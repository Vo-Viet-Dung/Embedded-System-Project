//Turn on motor/////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//						       Sample codes for Lab #1 							   //
/////////////////////////////////////////////////////////////////////////////////////
#include "reg51.h"

//Hex codes to display numbers (0-9) on a 7-segment anode display
code unsigned char LEDfont[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDpos=0;	//Choose 7-seg display position	

unsigned char oldkey=0xff;	//Push button data (release status)
unsigned char ledmode = 0;// che do hien thi led

//Define 7-seg anode display control (on/off):	
sbit LED7SEG_0 = P1^0;	//7-seg 1 anode display 
sbit LED7SEG_1 = P1^1;	//7-seg 2 anode display
sbit LED7SEG_2 = P1^2;	//7-seg 3 anode	display
sbit LED7SEG_3 = P1^3;	//7-seg 4 anode display

//Relay connects on P1^4
sbit JDQ  = P1^4;	//Relay on/off

//Buzzer (speaker) connects on P1^5 
sbit SPK  = P1^5;	//Buzzer on/off

//Define 6 push buttons on Port P3
sbit key1 = P3^7;	//Push button 1
sbit key2 = P3^6;	//Push button 2
sbit key3 = P3^5;	//Push button 3
sbit key4 = P3^4;	//Push button 4
sbit key5 = P3^3;	//Push button 5
sbit key6 = P3^2;	//Push button 6
			
//Delay 0-65536
void delay(unsigned int time)   
{							    
	while(time--);
}

void display(unsigned int da)
{
	P0=0xFF;			//Port 0 data off
	da=da%10000;	 	//Output data for 4 7-seg displays (4-digits)
	switch(LEDpos){
	// case 0:		//Choose 7-seg display #1
	// 	LED7SEG_0=0;
	// 	LED7SEG_1=1;	
	// 	LED7SEG_2=1;		
	// 	LED7SEG_3=1;
	// 	P0=LEDfont[da/1000];	//The Digit-4 (Thousands)
	// 	break;
	// case 1:		//Choose 7-seg display #2
	// 	LED7SEG_0=1;
	// 	LED7SEG_1=0;	
	// 	LED7SEG_2=1;		
	// 	LED7SEG_3=1;
	// 	P0=LEDfont[da%1000/100]; //The Digit-3 (Hundreds)
	// 	break;
	case 2:		//Choose 7-seg display #3
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=0;		
		LED7SEG_3=1;
		P0=LEDfont[da%100/10];  //The Digit-2 (Tens)
		break;
	case 3:		//Choose 7-seg display #4
		LED7SEG_0=1;
		LED7SEG_1=1;	
		LED7SEG_2=1;		
		LED7SEG_3=0;
		P0=LEDfont[da%10];	 //The Digit-1 (Units)
		break;
	}
	LEDpos++;		//Turn around
	if(LEDpos>3)
		LEDpos=0;	
}
//Read buttons 1-> 6 on P3
unsigned char ReadKey(void)	
{
	unsigned char lkey=0;
	if((P3&0xfc)!=0xfc){	//If any buttons pressed

		//SPK=1;				//Turn on buzzer
		//JDQ=1; 				//Turn on motor

		delay(10);			//Delay for buzzer pulse
		if(oldkey!=(P3&0xfc)){	//if any buttons pressed
			oldkey=P3&0xfc;		//Update button's values		
			if(key1==0)
				lkey=1;			//Button 1 pressed
			else if(key2==0)
				lkey=2;			//Button 2 pressed
			else if(key3==0)
				lkey=3;			//Button 3 pressed
			else if(key4==0)
				lkey=4;			//Button 4 pressed
			else if(key5==0)
				lkey=5;			//Button 5 pressed
			else if(key6==0)
				lkey=6;			//Button 6 pressed
		}
	}
	else{
		oldkey=0xfc;		//Default data of buttons port

		//SPK=0;				//Turn off buzzer
		//JDQ=0; 				//Turn off motor
	}
	return lkey;
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

// Ham delay 1ms
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

// Ham hien thi thoa man tu 00 den 99 giay
void hienThi(unsigned char giay)
{
	 unsigned char hangChuc, hangDonVi, i;
	 hangChuc = giay/10; hangDonVi = giay%10;

	 for(i=0;i<100;i++)
	 {
	 	LED7SEG_3 = 0; P0 = LEDfont[hangChuc]; delay_ms(5); LED7SEG_2 = 1;
		LED7SEG_2 = 0; P0 = LEDfont[hangDonVi]; delay_ms(5); LED7SEG_3 = 1;
	 } 
}

//Main program				
void main(void) 
{
	unsigned int LEDdata=0;		//7-seg 4-digit data 
	unsigned char i;
	unsigned int giay = 0;
	unsigned int run = 0;

	SPK = 0;	  
	JDQ = 0; 
	P1 = 0x0f;
	P2 = 0xff;			//All LED off
	P0 = 0;				//Port 0 connects to LCD
	
	while(1){			//Forever loop
		P2 = 0x00;		//8 LEDs on Port 2

		if(run == 1) {
			hienThi(giay);
			if(giay > 0) --giay;
			else {
				JDQ = 0;
				run = 0;
				LEDdata = 0;
				display(LEDdata);
				SPK = 1;
				for(i=0;i<3;i++)
					hienThi(giay);
				SPK = 0;
			}
		}
		else{
			JDQ = 0;
			display(LEDdata);		//Display 4 digits on 4 7-seg displays
			delay(100);
		}

		switch(ReadKey()){		//Polling push buttons
			case 6:	
				{
					giay = LEDdata;
					JDQ = 1;
					run = 1;		//button 1 pressed
				}
				break;
			case 5:
				{
					LEDdata = giay;
					JDQ = 0;
					run = 0;		//button 2 pressed	
				}
				break;	
			case 4:
				if(LEDdata < 99) LEDdata++;		//Button 3 pressed
				break;
			case 3:
				if(LEDdata > 0) LEDdata--;		//Button 4 pressed
				break;
		}	
	}
}
