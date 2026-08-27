#ifndef __SMG_H
#define __SMG_H

#include "stm32f10x.h"
#include "Delay.h"

/************ 数码管段选引脚定义（共阳） ************/
#define G_GPIO_PIN  GPIO_Pin_1
#define F_GPIO_PIN  GPIO_Pin_2
#define E_GPIO_PIN  GPIO_Pin_3
#define D_GPIO_PIN  GPIO_Pin_4
#define C_GPIO_PIN  GPIO_Pin_5
#define B_GPIO_PIN  GPIO_Pin_6
#define A_GPIO_PIN  GPIO_Pin_7

#define SMG_DUAN_GPIO   GPIOB   // 段选端口
#define SMG_WEI_GPIO    GPIOA   // 位选端口

/************ 位选引脚 ************/
#define SMG_1 GPIO_Pin_15
#define SMG_2 GPIO_Pin_14
#define SMG_3 GPIO_Pin_13
#define SMG_4 GPIO_Pin_12

/************ 数码管编码 ************/
extern unsigned char code[];

/************ 函数声明 ************/

/**
 * @brief 段码 GPIO 初始化
 */
void smg_duanma(void);

/**
 * @brief 位码 GPIO 初始化
 */
void smg_weima(void);

/**
 * @brief 段码显示函数（底层）
 * @param GPIOx 端口
 * @param val   显示的数值
 */

void smg_data(char weizhi, char num);

#endif
