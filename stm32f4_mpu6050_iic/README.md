# STM32-HAL库硬件IIC方式驱动MPU6050


本仓库包含以下内容：

1. MPU6050驱动文件
2. HAL工程
3. keil5工程


## 使用说明

1. 该例程可直接烧录至STM32F4芯片运行，使用了芯片的I2C2
2. 如果移植请注意在mpu6050.h文件的宏定义中修改使用的I2C
3. 详细配置请查阅HAL配置及程序注释