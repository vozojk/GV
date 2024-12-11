#pragma once

#include <windows.h>
DWORD WINAPI MyThreadStarter(LPVOID lpParam);
class clsRandomGen
{
private:
	bool mblThreadStop;
	int mintActNumber;
	CRITICAL_SECTION mCSGenerator;
public:
	clsRandomGen();
	~clsRandomGen();
	void ThreadGen();     // thread generování èísel
	int GetRND();      // vrací aktuální èíslo
};

