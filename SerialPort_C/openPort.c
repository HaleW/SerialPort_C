#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

/*打开串口*/
bool openPort(char *portName)
{
	hCom = CreateFile(
		portName,					  //串口号（将要打开的串口逻辑名）
		GENERIC_READ | GENERIC_WRITE, //允许读写（指定串口访问的类型）
		0,							  //指定共享属性，由于串口不能共享，该参数必须置为 0
		NULL,						  //引用安全性属性结构，缺省值为 NULL
		OPEN_EXISTING,				  //创建标志，对串口操作该参数必须置为 OPEN_EXISTING
		FILE_FLAG_OVERLAPPED,		  //异步I/O（属性描述，用于指定该串口是否进行异步操作，该值为 FILE_FLAG_OVERLAPPED，表示使用异步的 I/O；该值为 0，表示同步 I/O 操作）
		NULL						  //对串口而言该参数必须置为 NULL
	);

	/*串口打开成功返回其句柄，否则返回INVALID_HANDLE_VALUE（0XFFFFFFFF）*/
	if (hCom == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hCom);	//关闭串口
		printf("\t打开串口失败！\n");
		return false;
	}
	
	return true;
}