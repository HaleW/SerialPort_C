#pragma once
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>

HANDLE hCom; //���ھ����ȫ�ֱ�����



bool openPort(char *portName);

bool setCommState(int baudRate);
bool timeouts();
bool purgeComm();

char readFile();