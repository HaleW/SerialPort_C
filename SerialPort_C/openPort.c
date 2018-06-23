#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

/*�򿪴���*/
bool openPort(char *portName)
{
	hCom = CreateFile(
		portName,					  //���ںţ���Ҫ�򿪵Ĵ����߼�����
		GENERIC_READ | GENERIC_WRITE, //�����д��ָ�����ڷ��ʵ����ͣ�
		0,							  //ָ���������ԣ����ڴ��ڲ��ܹ����ò���������Ϊ 0
		NULL,						  //���ð�ȫ�����Խṹ��ȱʡֵΪ NULL
		OPEN_EXISTING,				  //������־���Դ��ڲ����ò���������Ϊ OPEN_EXISTING
		FILE_FLAG_OVERLAPPED,		  //�첽I/O����������������ָ���ô����Ƿ�����첽��������ֵΪ FILE_FLAG_OVERLAPPED����ʾʹ���첽�� I/O����ֵΪ 0����ʾͬ�� I/O ������
		NULL						  //�Դ��ڶ��Ըò���������Ϊ NULL
	);

	/*���ڴ򿪳ɹ��������������򷵻�INVALID_HANDLE_VALUE��0XFFFFFFFF��*/
	if (hCom == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hCom);	//�رմ���
		printf("\t�򿪴���ʧ�ܣ�\n");
		return false;
	}
	
	return true;
}