#include "clsRandomGen.h"
#include <time.h>
#include <iostream>

//
// // Start Threadu
//
DWORD WINAPI MyThreadStarter(LPVOID lpParam)
{
	clsRandomGen* lobjGen;
	lobjGen = (clsRandomGen*)lpParam;
	lobjGen->ThreadGen();
	return 0;
}
//
// // konstruktor
//
clsRandomGen::clsRandomGen() 
{
	//init critick� sekce
	InitializeCriticalSection(&mCSGenerator);

	//seed generator

	srand(time(NULL));
	
	mintActNumber = rand();
	 //thread bue b�et
	 mblThreadStop = false;

}
//
// // destruktor
//
clsRandomGen::~clsRandomGen() 
{
	mblThreadStop = true;

	//delete critick� sekce
	DeleteCriticalSection(&mCSGenerator);
}
//
// // thread generov�n� ��sel
//
void clsRandomGen::ThreadGen()
{
	try 
	{
		do {
			//vstoupit
			EnterCriticalSection(&mCSGenerator);

			//generovat ��slo
			mintActNumber = rand();

			//vystoupit
			LeaveCriticalSection(&mCSGenerator);


		} while (mblThreadStop == false);

	}
	catch (...)
	{
		LeaveCriticalSection(&mCSGenerator);
	}
	
}
//
// // vrac� aktu�ln� ��slo
//
int clsRandomGen::GetRND()     
{
	int lintNumber;

	//vstoupit
	EnterCriticalSection(&mCSGenerator);

	lintNumber = mintActNumber;

	//vystoupit
	LeaveCriticalSection(&mCSGenerator);
	return lintNumber;
}