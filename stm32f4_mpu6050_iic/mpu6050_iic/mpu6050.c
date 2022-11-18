//mpu6050.c
#include "mpu6050.h"
#include <math.h>

mpu6050 Mpu6050_Dat = {0};


/* 写一个字节 */
uint8_t MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
    if(HAL_I2C_Mem_Write(&MPU6050_I2C, MPU6050_SLAVE_ADDRESS, reg_add, I2C_MEMADD_SIZE_8BIT, &reg_dat, 1, 0xff) == HAL_OK)
    {
        HAL_Delay(1);
        return SUCCESS;
    }
    return ERROR;
}

/* 读取一个字节 */
uint8_t MPU6050_ReadData(uint8_t reg_add,unsigned char* Read,uint8_t num)
{
    if(HAL_I2C_Mem_Read(&MPU6050_I2C, MPU6050_SLAVE_ADDRESS | 0x01, reg_add, I2C_MEMADD_SIZE_8BIT, Read, num, 0xff) == HAL_OK)
    {
        HAL_Delay(1);
        return SUCCESS;
    }
    return ERROR;
}

/* 初始化 */
void MPU6050_Init(void)
{
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	    //解除休眠状态
		HAL_Delay(200);//解除休眠后延迟>100ms
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x03);			//选择时钟
		MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV, 0x00);	     //陀螺仪采样率，1KHz
    MPU6050_WriteReg(MPU6050_RA_CONFIG, 0x03);	         //低通滤波器的设置，加速度44hz滤波，陀螺仪42hz滤波
    MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG, 0x08);	   //配置加速度传感器工作在4G模式，不自检
    MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
}

/* 获取ID 0x68 */
uint8_t MPU6050ReadID(void)
{
    unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);
    return Re;
}

/* 获取原始三轴加速度 */
uint8_t MPU6050ReadAcc(mpu6050 *data)
{
    uint8_t buf[6];
    if(!MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6))
    {
        data->ax = (short)(buf[0] << 8) | buf[1];
        data->ay = (short)(buf[2] << 8) | buf[3];
        data->az = (short)(buf[4] << 8) | buf[5];
        return SUCCESS;
    }
    return ERROR;
}

/* 获取原始三轴角速度 */
uint8_t MPU6050ReadGyro(mpu6050 *data)
{
    uint8_t buf[6];
    if(!MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6))
    {
        data->gx = (short)(buf[0] << 8) | buf[1];
        data->gy = (short)(buf[2] << 8) | buf[3];
        data->gz = (short)(buf[4] << 8) | buf[5];
        return SUCCESS;
    }
    return ERROR;
}

/* 获取温度 */
uint8_t MPU6050_ReturnTemp(mpu6050 *data)
{
    short temp3;
    uint8_t buf[2];
    if(!MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2))
    {
        temp3= (buf[0] << 8) | buf[1];
        data->Temperature =((double) temp3/340.0)+36.53;
        return SUCCESS;
    }
    return ERROR;
}
