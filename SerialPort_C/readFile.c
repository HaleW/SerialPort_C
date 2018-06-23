#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>
#include "SerialPort.h"

char readFile()
{
	char lpInBuffer[1024];	//��������ݽ��洢���Ը�ָ���ֵΪ�׵�ַ��һƬ�ڴ���
	DWORD dwBytesRead = 1024; //Ҫ��������ݵ��ֽ���
	DWORD dwErrorFlag;		  //���մ�����ı���
	OVERLAPPED overlapped;	//�ص�I/O��һЩ��Ϣ
	COMSTAT comstat;		  //ͨ�Ŷ˿�״̬�ṹ����
	bool flag = true;
	while (true)
	{
		//������ڴ�����߶�ȡ�������ڵ�״̬
		ClearCommError(
			hCom,		  //���ھ��
			&dwErrorFlag, //���ش�����ֵ
			&comstat	  //ͨ�Ŷ˿�״̬�ṹ����
		);

		//������뻺�����е��ֽ���Ϊ0����"continue"
		if (comstat.cbInQue == 0)
		{
			if (flag)
			{
				printf("\tδ���յ�����!\n");
				flag = false;
			}
			continue;
		}

		//����������
		bool readFileFlag;
		readFileFlag = ReadFile(
			hCom,		  //���ھ��
			lpInBuffer,   //��������ݽ��洢���Ը�ָ���ֵΪ�׵�ַ��һƬ�ڴ���
			dwBytesRead,  //Ҫ��������ݵ��ֽ���
			&dwBytesRead, //ʵ�ʶ������ֽڸ���
			&overlapped   //�ص�����ʱ���ò���ָ��һ�� OVERLAPPED �ṹ
						  //ͬ������ʱ���ò���Ϊ NULL
		);
		//����������ʧ��
		if (!readFileFlag)
		{
			//�ص�������δ��ɣ��߳̿��Եȴ��������
			if (GetLastError() == ERROR_IO_PENDING)
			{
				GetOverlappedResult(
					hCom,		  //���ھ��
					&overlapped,  //ָ���ص�������ʼʱָ���� OVERLAPPED �ṹ
					&dwBytesRead, //�ñ�����ֵ����ʵ�ʶ�д����������ֽ���
					true		  //�ò�������ָ�������Ƿ�һֱ�ȵ��ص���������
								  //����ò���Ϊ TRUE������ֱ�����������ŷ���
								  //����ò���Ϊ FALSE������ֱ�ӷ��أ���ʱ�������û�����
				);
			}
		}
	}
	return lpInBuffer;
}