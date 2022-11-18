#ifndef __MPU_IIC_H
#define __MPU_IIC_H

#include "stm32f4xx_hal.h"


#define clock 168//主频
#define MPU6050_GPIO GPIOB
#define MPU6050_SDA GPIO_PIN_11
#define MPU6050_SCL GPIO_PIN_10
#define MPU6050_AD0 GPIO_PIN_9

#define	MPU6050_GPIO_CLK_ENABLE();   __HAL_RCC_GPIOB_CLK_ENABLE();//使能时钟线
/* 宏定义引脚电平操作函数 */
//#define MPU_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define MPU_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}  


#define MPU_IIC_SDA_1() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_SDA, GPIO_PIN_SET)
#define MPU_IIC_SDA_0() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_SDA, GPIO_PIN_RESET)

#define MPU_IIC_SCL_1() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_SCL, GPIO_PIN_SET)
#define MPU_IIC_SCL_0() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_SCL, GPIO_PIN_RESET)

//#define MPU_IIC_AD0_1() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_AD0, GPIO_PIN_RESET);
//#define MPU_IIC_AD0_0() HAL_GPIO_WritePin(MPU6050_GPIO, MPU6050_AD0, GPIO_PIN_RESET);

#define MPU_IIC_SDA_READ() HAL_GPIO_ReadPin( MPU6050_GPIO, MPU6050_SDA )

//#define MPU_IIC_Delay() delay_us(2)

/* 函数声明 */
void MPU_IIC_Init( void );
void MPU_IIC_Start( void );
void MPU_IIC_Stop( void );
uint8_t MPU_IIC_Wait_Ack( void );
void MPU_IIC_Ack( void );
void MPU_IIC_NAck( void );
void MPU_IIC_Send_Byte( uint8_t data );
uint8_t MPU_IIC_Read_Byte( uint8_t ack );
void MPU_SDA_IN();
void MPU_SDA_OUT();
void delay_us(uint16_t us);//微秒级延时，要注意修改


#endif

