#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

char readFile()
{
	char lpInBuffer[1024];	//读入的数据将存储在以该指针的值为首地址的一片内存区
	DWORD dwBytesRead = 1024; //要读入的数据的字节数
	DWORD dwErrorFlag;		  //接收错误码的变量
	OVERLAPPED overlapped;	//重叠I/O的一些信息
	COMSTAT comstat;		  //通信端口状态结构变量
	bool flag = true;
	while (true)
	{
		//清除串口错误或者读取串口现在的状态
		ClearCommError(
			hCom,		  //串口句柄
			&dwErrorFlag, //返回错误数值
			&comstat	  //通信端口状态结构变量
		);

		//如果输入缓冲区中的字节数为0，则"continue"
		if (comstat.cbInQue == 0)
		{
			if (flag)
			{
				printf("\t未接收到数据!\n");
				flag = false;
			}
			continue;
		}

		//读串口数据
		bool readFileFlag;
		readFileFlag = ReadFile(
			hCom,		  //串口句柄
			lpInBuffer,   //读入的数据将存储在以该指针的值为首地址的一片内存区
			dwBytesRead,  //要读入的数据的字节数
			&dwBytesRead, //实际读出的字节个数
			&overlapped   //重叠操作时，该参数指向一个 OVERLAPPED 结构
						  //同步操作时，该参数为 NULL
		);
		//读串口数据失败
		if (!readFileFlag)
		{
			//重叠操作还未完成，线程可以等待操作完成
			if (GetLastError() == ERROR_IO_PENDING)
			{
				GetOverlappedResult(
					hCom,		  //串口句柄
					&overlapped,  //指向重叠操作开始时指定的 OVERLAPPED 结构
					&dwBytesRead, //该变量的值返回实际读写操作传输的字节数
					true		  //该参数用于指定函数是否一直等到重叠操作结束
								  //如果该参数为 TRUE，函数直到操作结束才返回
								  //如果该参数为 FALSE，函数直接返回，这时如果操作没有完成
				);
			}
		}
	}
	return lpInBuffer;
}