#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

DCB dcb;//DCB 结构包含了诸如波特率、每个字符的数据位数、奇偶校验和停止位数等信息

bool setCommState(int baudRate)
{
	/**********获取当前串口属性**********/
	bool GetCommStateFlag;
	GetCommStateFlag = GetCommState(hCom, &dcb);
	if (!GetCommStateFlag)
	{
		printf("\t获取串口属性失败！\n");
		return false;
	}
	

	/**********设置相关串口属性**********/
	dcb.DCBlength = sizeof(dcb);//DCB结构体大小
	dcb.BaudRate = baudRate;	//设置波特率
	dcb.ByteSize = 8;			//数据宽度
	dcb.Parity = NOPARITY;		//无奇偶校验位
	dcb.StopBits = TWOSTOPBITS; //两个停止位

	bool SetCommStateFlag;
	SetCommStateFlag = SetCommState(hCom, &dcb);
	if (!SetCommStateFlag)
	{
		printf("\t设置串口属性失败！\n");
		return false;
	}


	/**********设定缓冲区大小**********/
	bool SetupCommFlag;
	SetupCommFlag = SetupComm(hCom, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024
	if (!SetupCommFlag)
	{
		printf("\t设置缓冲区大小失败！\n");
		return false;
	}

	return true;
}
bool timeouts()
{
	/**********设定读写超时**********/
	COMMTIMEOUTS Timeouts;

	/*设定读超时*/
	Timeouts.ReadIntervalTimeout = 1000;
	Timeouts.ReadTotalTimeoutConstant = 500;
	Timeouts.ReadTotalTimeoutMultiplier = 5000;

	/*设定写超时*/
	Timeouts.WriteTotalTimeoutConstant = 2000;
	Timeouts.WriteTotalTimeoutMultiplier = 500;
	bool SetCommTimeoutsFlag;
	SetCommTimeoutsFlag = SetCommTimeouts(hCom, &Timeouts); //设置超时
	if (!SetCommTimeoutsFlag)
	{
		printf("\t设置读写超时失败！\n");
		return false;
	}

	return true;
}
bool purgeComm()
{
	bool PurgeCommFlag;
	PurgeCommFlag = PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	if (!PurgeCommFlag)
	{
		printf("\t清除输入或输出缓冲区失败！\n");
		return false;
	}

	return true;
}