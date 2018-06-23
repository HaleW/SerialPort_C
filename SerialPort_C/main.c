
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <WinBase.h>

int main(void)
{
	openPort("com6");
	setCommState(9600);
	timeouts();
	purgeComm();
	readFile();
	return 0;
}