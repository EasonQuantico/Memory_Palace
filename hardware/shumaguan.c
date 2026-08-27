#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "Delay.h"  

unsigned char code[] ={0xC0, 0x79,0x24, 0x30, 0x19, 0x12, 0x02, 0x78,0x00, 0x10, 0x08, 0x03, 0x46,0x21, 0x06, 0x0e};//共阳数码管 显示点     
//段码初始化函数
#define G_GPIO_PIN  GPIO_Pin_1
#define F_GPIO_PIN  GPIO_Pin_0
#define E_GPIO_PIN  GPIO_Pin_3
#define D_GPIO_PIN  GPIO_Pin_4
#define C_GPIO_PIN  GPIO_Pin_5
#define B_GPIO_PIN  GPIO_Pin_6
#define A_GPIO_PIN  GPIO_Pin_7
//段码初始化函数
void smg_duanma(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = A_GPIO_PIN | B_GPIO_PIN | C_GPIO_PIN | D_GPIO_PIN | E_GPIO_PIN | F_GPIO_PIN | G_GPIO_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB, A_GPIO_PIN | B_GPIO_PIN | C_GPIO_PIN | D_GPIO_PIN | E_GPIO_PIN | F_GPIO_PIN | G_GPIO_PIN);
}    
//位码初始化
void smg_weima(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9| GPIO_Pin_8 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_SetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_12);    
}    

//数码管显示函数
void smg_data(char weizhi,char num)
{

      switch(weizhi)
        {
        
            case 1 : 
                    GPIO_SetBits(GPIOA, GPIO_Pin_10);    
                    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_12);    
										break;
            case 2 :
                    GPIO_ResetBits(GPIOA, GPIO_Pin_10);    
                    GPIO_SetBits(GPIOA, GPIO_Pin_9);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_12);    
                    break;
            case 3 : 
                    GPIO_ResetBits(GPIOA, GPIO_Pin_10);    
                    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
                    GPIO_SetBits(GPIOA, GPIO_Pin_8);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_12);    
										break;
            case 4 : 
                    GPIO_ResetBits(GPIOA, GPIO_Pin_10);    
                    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
                    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
                    GPIO_SetBits(GPIOA, GPIO_Pin_12);    
										break;
        }
       
        switch(num)
        {                                            
            case 0 :  //G不亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_SetBits(GPIOB, G_GPIO_PIN);
												break;
            case 1 : //只有bc亮 给0亮 给1灭
                    GPIO_SetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_SetBits(GPIOB, D_GPIO_PIN);
                    GPIO_SetBits(GPIOB, E_GPIO_PIN);
                    GPIO_SetBits(GPIOB, F_GPIO_PIN);
                    GPIO_SetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 2 : //只有abdf亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_SetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_SetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 3 : //只有abcdg亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_SetBits(GPIOB, E_GPIO_PIN);
                    GPIO_SetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 4 : //只有bcfg亮 给0亮 给1灭
                    GPIO_SetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_SetBits(GPIOB, D_GPIO_PIN);
                    GPIO_SetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 5 : //只有acdfg亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_SetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_SetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 6 : //只有acdefg亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_SetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 7 : //只有abc亮 给0亮 给1灭
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_SetBits(GPIOB, D_GPIO_PIN);
                    GPIO_SetBits(GPIOB, E_GPIO_PIN);
                    GPIO_SetBits(GPIOB, F_GPIO_PIN);
                    GPIO_SetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 8 : //                                    L
                    GPIO_SetBits(GPIOB, A_GPIO_PIN);
                    GPIO_SetBits(GPIOB, B_GPIO_PIN);
                    GPIO_SetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_SetBits(GPIOB, G_GPIO_PIN);
                        break;
            case 9 : //                                    A
                    GPIO_ResetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_SetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
						case 10 : //                                   H
                    GPIO_SetBits(GPIOB, A_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_SetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
						case 11 : //                                   b
                    GPIO_SetBits(GPIOB, A_GPIO_PIN);
                    GPIO_SetBits(GPIOB, B_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, C_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, D_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, E_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, F_GPIO_PIN);
                    GPIO_ResetBits(GPIOB, G_GPIO_PIN);
                        break;
        }

        //Delay_ms (1);                                                                   


        //GPIO_SetBits(GPIOB, A_GPIO_PIN | B_GPIO_PIN | C_GPIO_PIN | D_GPIO_PIN | E_GPIO_PIN | F_GPIO_PIN | G_GPIO_PIN  );
        //GPIO_SetBits(GPIOA, GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_12);

}


