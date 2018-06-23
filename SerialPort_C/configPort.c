#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

DCB dcb;//DCB �ṹ���������粨���ʡ�ÿ���ַ�������λ������żУ���ֹͣλ������Ϣ

bool setCommState(int baudRate)
{
	/**********��ȡ��ǰ��������**********/
	bool GetCommStateFlag;
	GetCommStateFlag = GetCommState(hCom, &dcb);
	if (!GetCommStateFlag)
	{
		printf("\t��ȡ��������ʧ�ܣ�\n");
		return false;
	}
	

	/**********������ش�������**********/
	dcb.DCBlength = sizeof(dcb);//DCB�ṹ���С
	dcb.BaudRate = baudRate;	//���ò�����
	dcb.ByteSize = 8;			//���ݿ��
	dcb.Parity = NOPARITY;		//����żУ��λ
	dcb.StopBits = TWOSTOPBITS; //����ֹͣλ

	bool SetCommStateFlag;
	SetCommStateFlag = SetCommState(hCom, &dcb);
	if (!SetCommStateFlag)
	{
		printf("\t���ô�������ʧ�ܣ�\n");
		return false;
	}


	/**********�趨��������С**********/
	bool SetupCommFlag;
	SetupCommFlag = SetupComm(hCom, 1024, 1024); //���뻺����������������Ĵ�С����1024
	if (!SetupCommFlag)
	{
		printf("\t���û�������Сʧ�ܣ�\n");
		return false;
	}

	return true;
}
bool timeouts()
{
	/**********�趨��д��ʱ**********/
	COMMTIMEOUTS Timeouts;

	/*�趨����ʱ*/
	Timeouts.ReadIntervalTimeout = 1000;
	Timeouts.ReadTotalTimeoutConstant = 500;
	Timeouts.ReadTotalTimeoutMultiplier = 5000;

	/*�趨д��ʱ*/
	Timeouts.WriteTotalTimeoutConstant = 2000;
	Timeouts.WriteTotalTimeoutMultiplier = 500;
	bool SetCommTimeoutsFlag;
	SetCommTimeoutsFlag = SetCommTimeouts(hCom, &Timeouts); //���ó�ʱ
	if (!SetCommTimeoutsFlag)
	{
		printf("\t���ö�д��ʱʧ�ܣ�\n");
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
		printf("\t�����������������ʧ�ܣ�\n");
		return false;
	}

	return true;
}