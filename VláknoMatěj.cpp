#include "clsRandomGen.h"
#include <iostream>
#include <windows.h>

int main()
{
	int choice{};
	int lintcislo;
	DWORD ldwThreadID;
	HANDLE lhThread;
	clsRandomGen* lobjRandomGen;

	printf("0 for new number 1 for end\n");
	//vytvoření objektu
	lobjRandomGen = new clsRandomGen();
	
	//start generování čísel
	lhThread = CreateThread(NULL, 0, MyThreadStarter, lobjRandomGen, 0, &ldwThreadID);

	
		
	//generovat
	


	while (true) {
		scanf_s("%i", &choice);
		if (choice == 0)
		{

			lintcislo = lobjRandomGen->GetRND();
			printf("%i\n", lintcislo);
			choice = 0;
		}
		if (choice == 1)
		{

			delete (lobjRandomGen);
			exit(0);
		}
	}
	



}

