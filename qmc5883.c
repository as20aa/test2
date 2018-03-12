#include "qmc5883.h"


extern int BUF[8]; 	//���ݻ���

void Delay_ms(unsigned int t)	
{						
	unsigned int i,j;				
	for(i=t;i>0;i--)
	for(j=121;j>0;j--);						
}
void Delay_5us()
{
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}
/**************************************
��ʼ�ź�
**************************************/
void QMC5883_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay_5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay_5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void QMC5883_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay_5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay_5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void QMC5883_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay_5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay_5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit QMC5883_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay_5us();                //��ʱ
    CY = SDA;                   //��λ��־ ��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay_5us();                //��ʱ
    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void QMC5883_SendByte(int dat)
{
    int i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay_5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay_5us();             //��ʱ
    }
    QMC5883_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
unsigned int QMC5883_RecvByte()
{
    int i;
    int dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay_5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay_5us();             //��ʱ
    }
    return dat;
}

//************************д�뵥�ֽ�����***************************

void Single_Write_QMC5883(int REG_Address,int REG_data)
{
    QMC5883_Start();                  //��ʼ�ź�
	//�˴���Slave_Address�������������ж���ģ�����������Ӻ������г��֣��Ҳ�����������ֻҪ����������������һ�ξ��ǶԺ����ɼ���
    QMC5883_SendByte(Slave_Address);   //�����豸��ַ+д�ź�
    QMC5883_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    QMC5883_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    QMC5883_Stop();                   //����ֹͣ�ź�
}

//************************��ȡ���ֽ�����*************************
//u8 Single_Read_QMC5883(u8 REG_Address)
//{   
//	u8 REG_data;
//	QMC5883_Start();                          //��ʼ�ź�
//	QMC5883_SendByte(Slave_Address);           //�����豸��ַ+д�ź�
//	QMC5883_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ	
//	QMC5883_Start();                          //��ʼ�ź�
//	QMC5883_SendByte(Slave_Address+1);         //�����豸��ַ+���ź�
//	REG_data=QMC5883_RecvByte();              //�����Ĵ�������
//	QMC5883_SendACK(1);   
//	QMC5883_Stop();                           //ֹͣ�ź�
//  return REG_data; 
//}

//******************************************************
//��������QMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x00~0x05
//******************************************************
void Multiple_Read_QMC5883()
{   
    int i;
    QMC5883_Start();                          //��ʼ�ź�
    QMC5883_SendByte(Slave_Address);          //�����豸��ַ+д�ź�
    QMC5883_SendByte(0x00);                   //���ʹ洢��Ԫ��ַ����0x00��ʼ	
    QMC5883_Start();                          //��ʼ�ź�
    QMC5883_SendByte(Slave_Address+1);        //�����豸��ַ+���ź�
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = QMC5883_RecvByte();          //BUF[0]�洢����
        if (i == 5)
        {
           QMC5883_SendACK(1);                //���һ��������Ҫ�ط�Ӧ��NOACK
        }
        else
        {
          QMC5883_SendACK(0);                 //Ӧ��ACK
       }
   }
    QMC5883_Stop();                           //ֹͣ�ź�
    Delay_ms(5);
}

//��ʼ��QMC5883��������Ҫ��ο�pdf�����޸�****
void Init_QMC5883()
{

	Single_Write_QMC5883(0x09,0x0d);  //���ƼĴ�������
	Single_Write_QMC5883(0x0b,0x01);  //�������ʱ��Ĵ���
	Single_Write_QMC5883(0x20,0x40);  //
	Single_Write_QMC5883(0x21,0x01);  //	
}



