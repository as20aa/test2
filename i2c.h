#ifndef __I2C_H__
#define __I2C_H__

#include <reg52.h>
#include <intrins.h>
#include "uart.h"

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

//sbit    SCL=P1^0;			//IICʱ�����Ŷ���
//sbit    SDA=P1^1;			//IIC�������Ŷ���

// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ����������ֵ��0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ


void  Delay5us(void);
void  I2C_Start(void);
void  I2C_Stop(void);
void  I2C_SendACK(bit ack);
unsigned char I2C_RecvACK();
void  I2C_SendByte(uchar dat);
void I2C_RecvByte(unsigned char* buf);
void  I2C_ReadPage();
void  I2C_WritePage();
void  display_ACCEL_x();
void  display_ACCEL_y();
void  display_ACCEL_z();
void Single_ReadI2C(uchar REG_Address,uchar temp[16]);						//��ȡI2C����
void  Single_WriteI2C(uchar REG_Address,uchar REG_data);	//��I2Cд������
void  InitMPU6050();													//��ʼ��MPU6050
#endif