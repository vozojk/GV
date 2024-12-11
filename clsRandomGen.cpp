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
	//init critické sekce
	InitializeCriticalSection(&mCSGenerator);

	//seed generator

	srand(time(NULL));
	
	mintActNumber = rand();
	 //thread bue bìžet
	 mblThreadStop = false;

}
//
// // destruktor
//
clsRandomGen::~clsRandomGen() 
{
	mblThreadStop = true;

	//delete critické sekce
	DeleteCriticalSection(&mCSGenerator);
}
//
// // thread generování èísel
//
void clsRandomGen::ThreadGen()
{
	try 
	{
		do {
			//vstoupit
			EnterCriticalSection(&mCSGenerator);

			//generovat èíslo
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
// // vrací aktuální èíslo
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