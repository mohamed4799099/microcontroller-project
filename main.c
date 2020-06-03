//////* take data from uart until '#' example --> 511234# , '5' is the number of room and '1' is state and '1234' is password */////////////
////// 4akl l data for uart
////*       12345#511234# *//////
////* first string which equal 12345 is number of rooms *////
/////* second string which equal 511234 is the data from room which  '5' is the number of room and '1' is state and '1234' is password *///////
///////////////////////////////////////////////
#include"keypad.h"
#include"uart.h"
#include<stdio.h>
#include<string.h>
///* timers for delay *//////
#include "C:/Keil/EE319KwareSpring2020/inc/tm4c123gh6pm.h"
#include "stdint.h"
void SystemInit(){}
void PllInit(){}
void SYSTICK_Init(void){
NVIC_ST_CTRL_R=0;
NVIC_ST_RELOAD_R=0X00FFFFFF;
NVIC_ST_CURRENT_R=0;
NVIC_ST_CTRL_R=0X00000005;		
}
void sysTick_wait(uint32_t delay){
	NVIC_ST_RELOAD_R=delay-1;
	NVIC_ST_CURRENT_R=0;
	while((NVIC_ST_CTRL_R & 0X00010000) ==0 ){}
	}
void sysTick_wait10ms(uint32_t delay){
	uint32_t i;
	for(i=0;i<delay;i++){
		sysTick_wait(8000);
	}
}
////////////////////////////////
void port_f_Init (void){
	uint32_t delay;
SYSCTL_RCGCGPIO_R |= (0X00000020);
	delay=1;
GPIO_PORTF_DIR_R=0X0E;
GPIO_PORTF_DEN_R=0X1F;
GPIO_PORTF_LOCK_R= 0X4C4F434B;
GPIO_PORTF_CR_R=0X1F;
	
}
//////////////* for solenoid *///////////////
void port_c_Init(void){
	uint32_t m;
	SYSCTL_RCGCGPIO_R |=(1<<2);
	m=1;
	GPIO_PORTC_DIR_R|=(1<<4);
	GPIO_PORTC_DEN_R |=(1<<4);
	GPIO_PORTC_AFSEL_R &=(~(1<<4));
	GPIO_PORTC_AMSEL_R &=(~(1<<4));
	GPIO_PORTC_PCTL_R &=(~(1<<4));
	GPIO_PORTC_PUR_R &=(~(1<<4));
}
typedef struct{
	uint8 room_number;
	uint8 state;
	uint8 *password;
}setup;


int main(){
	uint8 s[20]; //data of rooms         ///////="511234";
	 uint8 ps[20];
	uint8 ss[20]; // number of rooms            //////="12345";
	 uint8 temp[20];
	int p=0;
	 //uint8 *ps;
	 int i=0;
	 int m=0;
	 int ii=0;
	 int y=2;
	 int yy=0;
	 int n=0;
	 int len=0;
	 int flag=1;
	 int key22; //// data from keypad    //////////[5]={1,2,3,4};
	setup system[5];
	////* data of system *////
	system[0].room_number='1';
	system[0].state='0';
	strcpy(system[0].password,"0000");
	////
		system[1].room_number='2';
	system[1].state='1';
	strcpy(system[1].password,"1111");
	///
		system[2].room_number='3';
	system[2].state='0';
	strcpy(system[2].password,"1234");
	////
		system[3].room_number='4';
	system[3].state='1';
	strcpy(system[3].password,"1234");
	/////
		system[4].room_number='5';
	system[4].state='0';
	strcpy(system[4].password,"1122");
	
	
	
	
	/////////////////////////////////
	UART_init();
port_f_Init();
	 port_c_Init();
	SYSTICK_Init();
	GPIO_PORTF_DATA_R=0;
PllInit();
/*
GPIO_PORTF_DATA_R=0x00;
	while(1){
		GPIO_PORTF_DATA_R=0x02;
	}
	*/
//port_f_Init ();
	//GPIO_PORTF_DATA_R=0;
	//UART_receiveString(s);
	 /*
	 UART_receiveString(s);
	 UART_sendString(s);
	while(s[ii]!='\0'){
			len++;
			ii++;
			}

	_delay_ms(1500);
*/
 UART_receiveString(ss); ///// number of rooms
 sysTick_wait10ms(150);
 
	while(1){
		/////////
UART_receiveString(s); //// data of one room
			while(s[ii]!='\0'){
					len++;
					ii++;
					}
      sysTick_wait10ms(150);
		/////*cleaning*////////////////
		for(p=0;p<strlen(ss);p++){
			if(s[0]==ss[p]){
		if(s[1]=='2'){
					//GPIO_PORTF_DATA_R=0x02;
			GPIO_PORTC_DATA_R|=(1<<4); ///////// solenoid is on
				}
		/////*     free 8orfa *//////////////
		
				if(s[1]=='0'){
					//GPIO_PORTF_DATA_R=0;
					GPIO_PORTC_DATA_R&=(~(1<<4)); ///// solenoid is of
					
				}
      
      while(i<(len-2)){
		key22 = KeyPad_getPressedKey();
		ps[m]=key22+'0';             /////////[i]+'0';
		m++;
		i++;
				sysTick_wait10ms(50);
		
        }

		///////////////* 7agz *//////////


		if(s[1]=='1'){
			while(s[y]!='\0'){
				temp[n]=s[y];
				n++;
				y++;
			}

		for(yy=0;yy<n;yy++){
			if(ps[yy]!=temp[yy]){
				flag=0;
			}
		}
		if(flag==1){
		//GPIO_PORTF_DATA_R=0x02;
			GPIO_PORTC_DATA_R|=(1<<4); //// solenoid on 
		}
		}
}
		
			}
}
	}



