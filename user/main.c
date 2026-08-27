#include "stm32f10x.h"                  
#include "Delay.h"
#include "OLED.h"
#include "math.h"
int i;
int set;
int tone;
int t;
double b;
int key_flag = 0;
int count = 0;
#define MAX_NUMS 24
int nums[MAX_NUMS]={0},n[MAX_NUMS]={0};
int song_tone[500];
int song_time[500];
int song_note[500];
void TIM1_config(double Cycle);
void TIM2_config(int PulseNum);
void Pulse_output(double  Cycle,int PulseNum);
void TIM2_IRQHandler(void);
void notes(int note,int tone,int t);
void real_notes(int rn[i]);
int read_number_key(void);
void delete_last_number(void);

int main(void)
{

	OLED_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9|EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
       
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
       
        GPIO_SetBits(GPIOA, GPIO_Pin_11);
			 
			 start:
	OLED_ShowString(1,1,"SYHQ_E-Piano");
	OLED_ShowString(2,1,"SET_1 Playing");
	OLED_ShowString(3,1,"SET_2 Recording");
	OLED_ShowString(4,1,"SET_3 Songs");
		
	while (1){	
/*******************************************************************************************/		
		if(set==1){
			OLED_Clear();
			while(1){
		
		OLED_ShowString(1,1,"SYHQ_E-Piano");
			
		if (tone == 1){
			for ( i = 0; i < 12; i++) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
            Delay_ms(20); 
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
							b=i;
               Pulse_output(220*pow(2,(b-9)/12),50);
						}
					}
				}
		}
		if(tone == 2){
			for ( i = 0; i < 12; i++) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
            Delay_ms(20); 
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
							b=i;
               Pulse_output(440*pow(2,(b-9)/12),100);
						}
					}
				}
		}
		if(tone == 3){
			for ( i = 0; i < 12; i++) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
            Delay_ms(20); 
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
							b=i;
               Pulse_output(880*pow(2,(b-9)/12),200);
						}
					}
				}
		}
		switch(tone){
			case 1:OLED_ShowChar(2,1,'L');break;
			case 2:OLED_ShowChar(2,1,'M');break;
			case 3:OLED_ShowChar(2,1,'H');break;
			default :OLED_ShowChar(2,1,'-');
		}
		
		if(b==1||b==3||b==6||b==8||b==10)
			OLED_ShowChar(2,2,'#');
		else
			OLED_ShowChar(2,2,' ');
		OLED_ShowNum(2,3,key_flag,1);
		
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
			set = 0;
			goto start;
		}
	}
	}
/*******************************************************************************************/
	if(set == 2){
		OLED_Clear ();
		OLED_ShowString(1,1,"SYHQ_E-Piano");
		while (1) {
			
        int num = read_number_key();
        if (num > 0 && count < MAX_NUMS) {
            nums[count++] = num;
        }
				for(i=0;i<count;i++)
					switch(nums[i]){
						case 1:nums[i]=1111;break;
						case 2:nums[i]=111;break;
						case 3:nums[i]=2222;break;
						case 4:nums[i]=222;break;
						case 5:nums[i]=3333;break;
						case 6:nums[i]=4444;break;
						case 7:nums[i]=444;break;
						case 8:nums[i]=5555;break;
						case 9:nums[i]=555;break;
						case 10:nums[i]=6666;break;
						case 11:nums[i]=666;break;
						case 12:nums[i]=7777;break;
						default :break;
					}
				record:
			
			for(i=0;i<count;i++){
				if(i<8){
					if(nums[i]==111||nums[i]==222||nums[i]==444||nums[i]==555||nums[i]==666)
						OLED_ShowChar(2,2*i+1,'#');
				OLED_ShowNum(2,2*i+2,nums[i],1);
				}
				if(i>7&&i<16){
					if(nums[i]==111||nums[i]==222||nums[i]==444||nums[i]==555||nums[i]==666)
						OLED_ShowChar(3,2*i-15,'#');
					OLED_ShowNum(3,2*i-14,nums[i],1);
				}
				if(i>15){
					if(nums[i]==111||nums[i]==222||nums[i]==444||nums[i]==555||nums[i]==666)
						OLED_ShowChar(4,2*i-31,'#');
					OLED_ShowNum(4,2*i-30,nums[i],1);
				}
			}
        // ɾ     PB7
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
            Delay_ms(100);
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
                delete_last_number();
							OLED_Clear ();
							OLED_ShowString(1,1,"SYHQ_E-Piano");
							goto record;
            }
        }
				
        //    ż  PB6
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
            Delay_ms(20);
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
                for(i=0;i<count;i++){
									notes(nums[i],2,500);
								}           
            }
        }
				if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
					set= 0;
					goto start;
				}
			}
	}
/*******************************************************************************************/
	if(set == 3){
		song:
		OLED_ShowString(2,1,"Song_1          ");
		OLED_ShowString(3,1,"Song_2          ");
		OLED_ShowString(4,1,"Song_3          ");
		while(1){
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0){
			OLED_Clear();
			OLED_ShowString(1,1,"SYHQ_E-Piano");
			//С    
			int song_note[] = {1,1,5,5, 6,6,5, 4,4,3,3, 2,2,1, 5,5,4,4, 3,3,2, 5,5,4,4, 3,3,2, 1,1,5,5, 6,6,5, 4,4,3,3, 2,2,1, 99};
			for(i=0;song_note[i]!=99;i++)
				real_notes(song_note);
			int song_time[] = {1,1,1,1, 1,1,2, 1,1,1,1, 1,1,2, 1,1,1,1, 1,1,2, 1,1,1,1, 1,1,2, 1,1,1,1, 1,1,2, 1,1,1,1, 1,1,2, 99};
				for(i=0;song_time[i]!=99;i++){
				switch(song_time[i]){
						case 1:song_time[i]=300;break;
						case 2:song_time[i]=600;break;
				}
			}
			for(i=0;song_note[i]!=99;i++){
									notes(song_note[i],2,song_time[i]);
								}         
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0){
			OLED_Clear();
			OLED_ShowString(1,1,"SYHQ_E-Piano");
			//K  ֮  
			int song_note[] = {1,2, 3,2,1, 7,5, 1,7,1, 5,1, 4,4,5,4, 3,4,3,5, 6,7, 1,1,2, 3,2,1, 7,5, 1,7,1, 5,0, 1,7,1, 5,1,
								1,7,1, 2,1,2, 3,2,1, 7,5, 1,7,1, 5,6, 4,3,2,4, 3,2,1,5, 6,1,2, 1, 0,1,3,5, 7,2, 0,1,5,3, 4,3,5,6,
								5,6,1,3, 5,6, 0,5,3,1, 4,3,1, 2,1,3,5, 7,2, 0,1,7,1, 2,1,5,3, 1,1,2,3, 3,6, 4,3,4,6, 5, 0,5,6,7,
								3,1, 7,5,6,7, 6,7,6,5, 3,0,6,7,1, 4,1,1, 3,2,1,6, 4,4,6,1,3, 2,5,6,7, 3,1, 7,5,7,6, 3,2,1,6,
								3,0,6,7,11, 4,1,1, 3,2,1,6, 1,1,1,1,2,3, 2,2,1, 7,1, 7,5, 6,6,6,5,3, 1, 0,1,2,3, 4,4,1,7, 5,1,
								4,4,4,3, 6,7, 1, 1,1,2, 3,2,1, 7,5, 1,7,1, 5,1, 4,4,5,4, 3,4,3,5, 6,7, 1,1,2, 3,2,1, 7,5, 1,7,1, 
								5,0, 1,7,1, 5,1, 1,7,1, 2,1,2, 3,2,1, 7,5, 1,7,1, 5,6, 4,3,2,4, 3,2,1,3, 2,3,4,1, 5,5,6,7,
								3,1, 7,5,6,7, 6,7,6,5, 3,0,6,7,1, 4,1,1, 3,2,1,6, 4,4,6,1,3, 2,5,6,7, 3,1, 7,5,7,6, 3,2,1,6,
								3,0,6,7,11, 4,1,1, 3,2,1,6, 1,1,1,1,2,3, 2,2,1, 7,7,1,7,7,1, 7,7,6,5,5, 1,1,1,1,2,1, 3,2,1,
								7,7,1,7,7,1, 7,7,6,5,5, 6,6,6,6,5,3, 1,1,2,3, 4,4,1,7, 5,1, 4,4,4,3, 6,7, 1, 0,0, 0,1,2,
								7,5, 1,7,1, 5,1, 4,4,5,4, 3,4,3,5, 6,6,1,3,7, 1,0, 99};
			for(i=0;song_note[i]!=99;i++)
				real_notes(song_note);
			int song_tone[] = {2,2, 2,2,2, 1,1, 2,1,2, 1,2, 2,2,2,2, 2,2,2,1, 1,1, 2,2,2, 2,2,2, 1,1, 2,1,2, 1,0, 2,1,2, 1,2,
										2,1,2, 2,2,2, 2,2,2, 1,1, 2,1,2, 1,2, 2,2,2,2, 2,2,2,1, 1,2,2, 1, 0,2,2,2, 2,3, 0,3,2,2, 2,2,2,2,
										2,1,2,2, 2,2, 0,2,2,2, 2,2,2, 2,2,2,2, 2,3, 0,3,2,3, 3,3,2,2, 2,2,2,2, 2,1, 2,2,2,2, 2, 0,2,2,2,
										3,3, 2,2,2,2, 2,2,2,2, 2,2,2,2,3, 3,3,3, 3,3,3,2, 2,2,2,3,3, 3,2,2,2, 3,3, 2,2,2,2, 3,3,3,2,
										2,0,2,2,3, 3,3,3, 3,3,3,2, 3,3,3,3,3,3, 3,3,3, 2,3, 2,2, 2,2,2,2,2, 2, 0,2,2,2, 2,2,2,2, 2,2,
										2,2,2,2, 1,1, 2, 2,2, 2,2,2, 1,1, 2,1,2, 1,2, 2,2,2,2, 2,2,2,1, 1,1, 2,2,2, 2,2,2, 1,1, 2,1,2, 
										1,0, 2,1,2, 1,2, 2,1,2, 2,2,2, 2,2,2, 1,1, 2,1,2, 1,2, 2,2,2,2, 2,2,2,2, 2,2,2,3, 2,2,2,2,
										3,3, 2,2,2,2, 2,2,2,2, 2,2,2,2,3, 3,3,3, 3,3,3,2, 2,2,2,3,3, 3,2,2,2, 3,3, 2,2,2,2, 3,3,3,2,
										2,0,2,2,3, 3,3,3, 3,3,3,2, 3,3,3,3,3,3, 3,3,3, 2,2,3,2,2,3, 2,2,2,2,2, 3,3,3,3,3,3, 3,3,3,
										2,2,3,2,2,3, 2,2,2,2,2, 2,2,2,2,2,2, 2,2,2,2, 2,2,3,2, 2,2, 2,2,2,2, 1,1, 2, 0,0, 0,2,2, 2,2,2,
										1,1, 2,1,2, 2,2, 2,2,2,2, 2,2,2,1, 1,1,2,2,2, 3,0};
			int song_time[] = {2,2, 4,2,2, 4,4, 4,2,2, 4,4, 2,2,2,2, 2,2,2,2, 4,4, 4,2,2, 4,2,2, 4,4, 4,2,2, 4,4, 4,2,2, 4,4,
									4,2,2, 4,2,2, 4,2,2, 4,4, 4,2,2, 6,2, 2,2,2,2, 2,2,2,2, 4,2,2, 8, 2,2,2,2, 4,4, 2,2,2,2, 2,2,2,2,
									2,2,2,2, 4,4, 2,2,2,2, 4,2,2, 2,2,2,2, 4,4, 2,2,2,2, 2,2,2,2, 2,2,2,2, 4,4, 2,2,2,2, 8, 2,2,2,2,
									4,4, 2,2,2,2, 2,2,2,2, 2,1,1,2,2, 4,3,1, 2,2,2,2, 2,2,1,1,2, 3,1,2,2, 4,4, 2,2,2,2, 2,2,2,2, 2,1,1,2,2,
									4,3,1, 2,2,2,2, 1,1,2,1,1,2, 4,2,2, 4,4, 4,4, 2,2,1,1,2, 8, 4,1,1,2, 4,1,1,2, 4,4, 4,1,1,2, 6,2, 12,
									2,2, 4,2,2, 4,4, 4,2,2, 4,4, 2,2,2,2, 2,2,2,2, 4,4, 4,2,2, 4,2,2, 4,4, 4,2,2, 4,4, 4,2,2, 4,4,
									4,2,2, 4,2,2, 4,2,2, 4,4, 4,2,2, 6,2, 2,2,2,2, 2,2,2,2, 4,1,1,2, 2,2,2,2, 4,4, 2,2,2,2, 2,2,2,2, 
									2,1,1,2,2, 4,3,1, 2,2,2,2, 2,2,1,1,2, 3,1,2,2, 4,4, 2,2,2,2, 2,2,2,2, 2,1,1,2,2, 4,3,1, 2,2,2,2, 
									1,1,2,1,1,2, 4,2,2, 1,1,2,1,1,2, 1,1,2,3,1, 1,1,2,1,1,2, 4,2,2, 1,1,2,1,1,2, 1,1,2,3,1, 1,1,2,1,1,2,
									4,1,1,2, 4,1,1,2, 4,4, 4,1,1,2, 6,2, 8, 4,4, 4,2,2, 4,2,2, 4,4, 4,2,2, 6,2, 2,2,2,2, 2,2,2,2, 3,1,1,1,2, 12,4, 99};
			for(i=0;song_time[i]!=99;i++){
				switch(song_time[i]){
						case 1:song_time[i]=150;break;
						case 2:song_time[i]=300;break;
						case 3:song_time[i]=450;break;
						case 4:song_time[i]=600;break;
						case 6:song_time[i]=900;break;
						case 8:song_time[i]=1200;break;
						case 12:song_time[i]=1800;break;
						default :break;
					}
			}
			for(i=0;song_note[i]!=99;i++){
									notes(song_note[i],song_tone[i],song_time[i]);
								}         
		
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0){
			OLED_Clear();
			OLED_ShowString(1,1,"SYHQ_E-Piano");
				//  ʿɽ  
	notes(1111,3,500);notes(6666,2,250);notes(1111,3,250);notes(3333,3,500);notes(3333,3,250);notes(2222,3,250);
	notes(3333,3,250);notes(2222,3,250);notes(3333,3,250);notes(2222,3,250);notes(1111,3,250);notes(666,2,250);notes(6666,2,250);notes(5555,2,250);
	notes(6666,2,500);notes(666,2,250);notes(1111,3,250);notes(2222,3,500);notes(3333,3,250);notes(4444,3,250);
	notes(5555,3,1000);notes(3333,3,250);notes(5555,3,500);notes(2222,3,250);
	notes(3333,3,125);notes(1111,3,125);notes(6666,2,125);notes(3333,2,125);notes(3333,3,125);notes(1111,3,125);notes(6666,2,125);notes(3333,2,125);
	notes(3333,3,125);notes(1111,3,125);notes(6666,2,125);notes(3333,2,125);notes(3333,3,125);notes(1111,3,125);notes(6666,2,125);notes(3333,2,125);
	notes(2222,3,125);notes(666,2,125);notes(5555,2,125);notes(2222,2,125);notes(2222,3,125);notes(666,2,125);notes(5555,2,125);notes(2222,2,125);
	notes(2222,3,125);notes(666,2,125);notes(5555,2,125);notes(2222,2,125);notes(2222,3,125);notes(666,2,125);notes(5555,2,125);notes(2222,2,125);
	notes(1111,3,125);notes(6666,2,125);notes(4444,2,125);notes(1111,2,125);notes(1111,3,125);notes(6666,2,125);notes(4444,2,125);notes(1111,2,125);
	notes(666,3,125);notes(5555,2,125);notes(2222,2,125);notes(666,2,125);notes(666,3,125);notes(5555,2,125);notes(2222,2,125);notes(666,2,125);
	notes(1111,3,2000);
	
	notes(0,0,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);notes(1111,2,375);notes(2222,1,325);notes(3333,2,250);
	notes(3333,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(5555,2,500);notes(3333,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,375);notes(2222,2,325);notes(2222,2,250);notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);
	notes(2222,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(5555,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(6666,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);notes(1111,2,375);notes(2222,2,325);notes(3333,1,250);
	notes(5555,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(6666,2,500);notes(5555,2,250);notes(3333,1,250);notes(3333,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,375);notes(2222,2,325);notes(2222,2,250);notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);
	notes(1111,2,750);notes(1111,2,250);notes(1111,3,250);notes(666,2,250);notes(1111,3,250);notes(6666,2,250);
	notes(1111,3,375);notes(6666,2,325);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);
	notes(6666,2,375);notes(6666,2,325);notes(6666,2,250);notes(6666,2,375);notes(5555,2,325);notes(6666,2,250);
	notes(5555,2,250);notes(3333,2,750);notes(0,0,250);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(6666,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(1111,2,250);notes(1111,2,250);
	notes(1111,3,375);notes(1111,3,325);notes(1111,3,250);notes(1111,3,375);notes(6666,2,325);notes(1111,3,250);
	notes(6666,2,750);notes(5555,2,500);notes(1111,3,250);notes(1111,3,250);notes(666,2,250);
	notes(1111,3,250);notes(666,2,250);notes(6666,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);
	notes(6666,2,375);notes(6666,2,325);notes(6666,2,250);notes(6666,2,375);notes(5555,2,325);notes(6666,2,250);
	notes(5555,2,250);notes(3333,2,750);notes(0,0,250);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(6666,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);notes(1111,3,1000);
	notes(0,0,1250);notes(1111,3,250);notes(6666,2,250);notes(1111,3,250);
	notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(2222,2,500);notes(1111,2,250);notes(6666,1,250);notes(1111,2,250);notes(1111,2,250);notes(2222,2,250);
	notes(1111,2,2000);
	
	notes(0,0,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);notes(1111,2,375);notes(2222,1,325);notes(3333,2,250);
	notes(3333,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(5555,2,500);notes(3333,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,375);notes(2222,2,325);notes(2222,2,250);notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);
	notes(2222,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(5555,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,250);notes(3333,2,500);notes(6666,2,500);notes(3333,2,250);notes(2222,1,250);notes(1111,2,250);
	notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);notes(1111,2,375);notes(2222,2,325);notes(3333,1,250);
	notes(5555,2,750);notes(5555,1,250);notes(6666,1,250);notes(1111,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(6666,2,500);notes(5555,2,250);notes(3333,1,250);notes(3333,2,250);
	notes(2222,2,250);notes(1111,2,500);notes(3333,2,500);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);
	notes(2222,2,375);notes(2222,2,325);notes(2222,2,250);notes(2222,2,375);notes(1111,2,325);notes(6666,1,250);
	notes(1111,2,750);notes(1111,2,250);notes(1111,3,250);notes(666,2,250);notes(1111,3,250);notes(6666,2,250);
	notes(1111,3,375);notes(6666,2,325);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);
	notes(6666,2,375);notes(6666,2,325);notes(6666,2,250);notes(6666,2,375);notes(5555,2,325);notes(6666,2,250);
	notes(5555,2,250);notes(3333,2,750);notes(0,0,250);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(6666,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(1111,2,250);notes(1111,2,250);
	notes(1111,3,375);notes(1111,3,325);notes(1111,3,250);notes(1111,3,375);notes(6666,2,325);notes(1111,3,250);
	notes(6666,2,750);notes(5555,2,500);notes(1111,3,250);notes(1111,3,250);notes(666,2,250);
	notes(1111,3,250);notes(666,2,250);notes(6666,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);
	notes(6666,2,375);notes(6666,2,325);notes(6666,2,250);notes(6666,2,375);notes(5555,2,325);notes(6666,2,250);
	notes(5555,2,250);notes(3333,2,750);notes(0,0,250);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(3333,2,250);notes(5555,2,250);notes(2222,2,250);notes(1111,2,500);notes(1111,2,250);notes(2222,2,250);notes(3333,2,250);
	notes(6666,2,250);notes(3333,2,250);notes(2222,2,250);notes(1111,2,250);notes(1111,3,1000);
	notes(0,0,1250);notes(1111,3,250);notes(6666,2,250);notes(1111,3,250);
	notes(6666,2,250);notes(5555,2,500);notes(5555,2,250);notes(6666,2,250);notes(5555,2,250);notes(3333,2,250);notes(2222,2,250);
	notes(3333,2,250);notes(2222,2,500);notes(1111,2,250);notes(6666,1,250);notes(1111,2,250);notes(1111,2,250);notes(2222,2,250);
	notes(1111,2,3250);notes(1111,3,250);notes(6666,2,250);notes(1111,3,250);
	notes(2222,3,250);notes(1111,3,500);notes(1111,3,250);notes(2222,3,250);notes(1111,3,250);notes(6666,2,250);notes(1111,3,250);
	notes(3333,3,250);notes(2222,3,500);notes(1111,3,250);notes(6666,2,250);notes(1111,3,250);notes(2222,2,500);
	notes(1111,2,2000);
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
			set = 0;
			goto start;
		}
		goto song;
		}
	}
}
}
/*******************************************************************************************/
void TIM1_config(double Cycle)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_TIM1 , ENABLE); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 10000-1;                                                   
    TIM_TimeBaseStructure.TIM_Prescaler =7200/Cycle-1;                                                                  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);                                       

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;          
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1000-1;                                      
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    

    TIM_OC4Init(TIM1, &TIM_OCInitStructure);                                                         

    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
    

    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);                              
    TIM_ARRPreloadConfig(TIM1, ENABLE);                                                          
}

void TIM2_config(int PulseNum)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = PulseNum-1;   
    TIM_TimeBaseStructure.TIM_Prescaler =0;    
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  

    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);
    TIM2->SMCR|=0x0f;                              
    TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;        
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);
}
void Pulse_output(double Cycle,int PulseNum)
{
    TIM2_config(PulseNum);
    TIM_Cmd(TIM2, ENABLE);
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM1_config(Cycle);
    
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);  
}

void TIM2_IRQHandler(void) 
{ 
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)     
    { 
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
        TIM_CtrlPWMOutputs(TIM1, DISABLE);
        TIM_Cmd(TIM1, DISABLE); 
        TIM_Cmd(TIM2, DISABLE);  
        TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
    } 
} 

void notes(int note,int tone,int t)
{
		switch(tone){
			case 1:
			switch(note){
				case 1111:Pulse_output(131,t/8);Delay_ms(t);break;
				case 111:Pulse_output(139,t/8);Delay_ms(t);break;
				case 2222:Pulse_output(147,t/8);Delay_ms(t);break;
				case 222:Pulse_output(156,t/8);Delay_ms(t);break;
				case 3333:Pulse_output(165,t/8);Delay_ms(t);break;
				case 4444:Pulse_output(175,t/8);Delay_ms(t);break;
				case 444:Pulse_output(185,t/8);Delay_ms(t);break;
				case 5555:Pulse_output(196,t/8);Delay_ms(t);break;
				case 555:Pulse_output(208,t/8);Delay_ms(t);break;
				case 6666:Pulse_output(220,t/8);Delay_ms(t);break;
				case 666:Pulse_output(233,t/8);Delay_ms(t);break;
				case 7777:Pulse_output(247,t/8);Delay_ms(t);break;
				default:Delay_ms(t);
			}break;
			case 2:
			switch(note){
				case 1111:Pulse_output(262,t/4);Delay_ms(t);break;
				case 111:Pulse_output(277,t/4);Delay_ms(t);break;
				case 2222:Pulse_output(294,t/4);Delay_ms(t);break;
				case 222:Pulse_output(311,t/4);Delay_ms(t);break;
				case 3333:Pulse_output(330,t/4);Delay_ms(t);break;
				case 4444:Pulse_output(349,t/4);Delay_ms(t);break;
				case 444:Pulse_output(367,t/4);Delay_ms(t);break;
				case 5555:Pulse_output(392,t/4);Delay_ms(t);break;
				case 555:Pulse_output(415,t/4);Delay_ms(t);break;
				case 6666:Pulse_output(440,t/4);Delay_ms(t);break;
				case 666:Pulse_output(466,t/4);Delay_ms(t);break;
				case 7777:Pulse_output(494,t/4);Delay_ms(t);break;
				default:Delay_ms(t);
			}break;
			case 3:
			switch(note){
				case 1111:Pulse_output(523,t/2);Delay_ms(t);break;
				case 111:Pulse_output(554,t/2);Delay_ms(t);break;
				case 2222:Pulse_output(587,t/2);Delay_ms(t);break;
				case 222:Pulse_output(622,t/2);Delay_ms(t);break;
				case 3333:Pulse_output(659,t/2);Delay_ms(t);break;
				case 4444:Pulse_output(698,t/2);Delay_ms(t);break;
				case 444:Pulse_output(740,t/2);Delay_ms(t);break;
				case 5555:Pulse_output(784,t/2);Delay_ms(t);break;
				case 555:Pulse_output(831,t/2);Delay_ms(t);break;
				case 6666:Pulse_output(880,t/2);Delay_ms(t);break;
				case 666:Pulse_output(932,t/2);Delay_ms(t);break;
				case 7777:Pulse_output(988,t/2);Delay_ms(t);break;
				default:Delay_ms(t);
			}break;
			default :break;
		}
		if(set == 3){
			switch(tone){
			case 1:OLED_ShowChar(2,1,'L');break;
			case 2:OLED_ShowChar(2,1,'M');break;
			case 3:OLED_ShowChar(2,1,'H');break;
			default :OLED_ShowChar(2,1,'-');
			}
			if(note==111||note==222||note==444||note==555||note==666)
				OLED_ShowChar(2,2,'#');
			else
				OLED_ShowChar(2,2,' ');
			OLED_ShowNum(2,3,note,1);
		}
}

void real_notes(int rn[i])
{
	switch(rn[i]){
						case 1:rn[i]=1111;break;
						case 11:rn[i]=111;break;
						case 2:rn[i]=2222;break;
						case 22:rn[i]=222;break;
						case 3:rn[i]=3333;break;
						case 4:rn[i]=4444;break;
						case 44:rn[i]=444;break;
						case 5:rn[i]=5555;break;
						case 55:rn[i]=555;break;
						case 6:rn[i]=6666;break;
						case 66:rn[i]=666;break;
						case 7:rn[i]=7777;break;
						default :break;
					}
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET){
		set = 2;
		tone = 2;
		EXTI_ClearITPendingBit(EXTI_Line0); 
	}
}
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET){
		set = 1;
		tone = 1;
		EXTI_ClearITPendingBit(EXTI_Line1); 
	}
}

void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) == SET){
		set = 3;
		tone = 3;
		EXTI_ClearITPendingBit(EXTI_Line3); 
	}
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) == SET){
		key_flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line4); 
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line5) == SET){
		key_flag =11;
		EXTI_ClearITPendingBit(EXTI_Line5); 
	}
	if (EXTI_GetITStatus(EXTI_Line6) == SET){
		key_flag = 2;
		EXTI_ClearITPendingBit(EXTI_Line6); 
	}
	if (EXTI_GetITStatus(EXTI_Line7) == SET){
		key_flag = 22;
		EXTI_ClearITPendingBit(EXTI_Line7); 
	}
	if (EXTI_GetITStatus(EXTI_Line8) == SET){
		key_flag = 3;
		EXTI_ClearITPendingBit(EXTI_Line8); 
	}
	if (EXTI_GetITStatus(EXTI_Line9) == SET){
		key_flag = 4;
		EXTI_ClearITPendingBit(EXTI_Line9); 
	}
}
	
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line10) == SET)
    {
         key_flag = 44;
         EXTI_ClearITPendingBit(EXTI_Line10); 
    }
	if (EXTI_GetITStatus(EXTI_Line11) == SET)
    {
         key_flag = 5;
         EXTI_ClearITPendingBit(EXTI_Line11); 
    }
	if (EXTI_GetITStatus(EXTI_Line12) == SET)
    {
         key_flag = 55;
         EXTI_ClearITPendingBit(EXTI_Line12); 
    }
	if (EXTI_GetITStatus(EXTI_Line13) == SET)
    {
         key_flag = 6;
         EXTI_ClearITPendingBit(EXTI_Line13); 
    }
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {
         key_flag = 66;
         EXTI_ClearITPendingBit(EXTI_Line14); 
    }
	if (EXTI_GetITStatus(EXTI_Line15) == SET)
    {
         key_flag = 7;
         EXTI_ClearITPendingBit(EXTI_Line15); 
    }
}

int read_number_key(void) {
    for ( i = 0; i < 12; i++) {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
            Delay_ms(20); 
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0) {
                while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4<<i) == 0); 
                return i+1; 
            }
        }
			}
		return 0;
}

void delete_last_number(void) {
    if (count > 0) {
        count--;
    } else {
        count=0;
    }
}
