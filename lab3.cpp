#include "lab3.h"
#include <windows.h>
#include <stdio.h>

using namespace std;

HANDLE Mutex;

HANDLE SemD, SemE, SemG, SemH, wait_interval, start_interval; // SemD, SemE, SemG, SemH are for DEGH; wait_interval, start_interval for sync

unsigned int lab3_thread_graph_id()
{
	return 4;
}

const char* lab3_unsynchronized_threads()
{
	return "efgh";
}

const char* lab3_sequential_threads()
{
	return "degh";
}


DWORD WINAPI thread_a(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'a' << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'b' << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}
DWORD WINAPI thread_c(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'c' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'c' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'd' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'd' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemD, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'd' << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemE, 1, NULL);
	}

	
	return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemE, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemG, 1, NULL);
	}
	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemG, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'g' << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemH, 1, NULL);
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'g' << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemH, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'h' << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemD, 1, NULL);
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'h' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	ReleaseSemaphore(wait_interval, 1, nullptr);    //current interval ended
	WaitForSingleObject(start_interval, INFINITE);  //start new interval

	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'h' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'f' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}
DWORD WINAPI thread_i(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'i' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}
DWORD WINAPI thread_k(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'k' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}
DWORD WINAPI thread_m(LPVOID lpParam)
{
	for (int i = 0; i < 4; i++) {
		WaitForSingleObject(Mutex, INFINITE);
		cout << 'm' << flush;
		ReleaseMutex(Mutex);
		computation();
	}

	return 0;
}




int lab3_init()
{
	Mutex = CreateMutex(NULL, FALSE, NULL);
	

	if (Mutex == NULL)
	{		
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}

	SemD = CreateSemaphore(NULL, 1, 1, NULL);
	if (SemD == NULL)
	{
		cout << "CreateSemaphore error: SemD" << GetLastError() << endl;
		return 1;
	}

	SemE = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemD == NULL)
	{
		cout << "CreateSemaphore error: SemE " << GetLastError() << endl;
		return 1;
	}

	SemG = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemD == NULL)
	{
		cout << "CreateSemaphore error: SemG" << GetLastError() << endl;
		return 1;
	}

	SemH = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemD == NULL)
	{
		cout << "CreateSemaphore error: SemH" << GetLastError() << endl;
		return 1;
	}

	wait_interval = CreateSemaphore(NULL, 0, 3, NULL);
	if (wait_interval == NULL)
	{
		cout << "CreateSemaphore error: wait_interval" << GetLastError() << endl;
		return 1;
	}
	start_interval = CreateSemaphore(NULL, 0, 3, NULL);
	if (start_interval == NULL)
	{
		cout << "CreateSemaphore error: start_interval" << GetLastError() << endl;
		return 1;
	}

	HANDLE threadA, threadB, threadC, threadD, threadE, threadF, threadG, threadH, threadI, threadK, threadM;

	//1-st interval
	threadA = CreateThread(NULL, 0, thread_a, NULL, 0, NULL);
	if (threadA == NULL) return GetLastError();

	threadC = CreateThread(NULL, 0, thread_c, NULL, 0, NULL);
	if (threadC == NULL) return GetLastError();

	threadD = CreateThread(NULL, 0, thread_d, NULL, 0, NULL);
	if (threadD == NULL) return GetLastError();

	threadE = CreateThread(NULL, 0, thread_e, NULL, 0, NULL);
	if (threadE == NULL) return GetLastError();

	WaitForSingleObject(threadA, INFINITE);                              //join with ended thread A
	WaitForSingleObject(wait_interval, INFINITE);                   //wait for thread C to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread D to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread E to finish

	//2-d interval

	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread C
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread D
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread E

	threadB = CreateThread(NULL, 0, thread_b, NULL, 0, NULL);
	if (threadB == NULL) return GetLastError();

	WaitForSingleObject(threadC, INFINITE);						//join with ended thread C
	WaitForSingleObject(threadB, INFINITE);						//join with ended thread B
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread D to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread E to finish

	//3-d interval
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread D
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread E


	threadG = CreateThread(NULL, 0, thread_g, NULL, 0, NULL);
	if (threadG == NULL) return GetLastError();

	threadH = CreateThread(NULL, 0, thread_h, NULL, 0, NULL);
	if (threadH == NULL) return GetLastError();
	WaitForSingleObject(threadD, INFINITE);						//join with ended thread D
	WaitForSingleObject(wait_interval, INFINITE);                   //wait for thread E to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread G to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread H to finish

	//4-th interval
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread G
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread E
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread H
	threadF = CreateThread(NULL, 0, thread_f, NULL, 0, NULL);
	if (threadF == NULL) return GetLastError();
	WaitForSingleObject(threadG, INFINITE);						//join with ended thread G
	WaitForSingleObject(threadE, INFINITE);						//join with ended thread E
	WaitForSingleObject(threadF, INFINITE);						//join with ended thread F
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread H to finish


	//5-th interval
	ReleaseSemaphore(start_interval, 1, NULL);            //continue thread H
	threadI = CreateThread(NULL, 0, thread_i, NULL, 0, NULL);
	if (threadI == NULL) return GetLastError();
	threadK = CreateThread(NULL, 0, thread_k, NULL, 0, NULL);
	if (threadK == NULL) return GetLastError();
	WaitForSingleObject(threadH, INFINITE);						//join with ended thread H
	WaitForSingleObject(threadI, INFINITE);						//join with ended thread I
	WaitForSingleObject(threadK, INFINITE);						//join with ended thread K

	//6-th interval
	threadM = CreateThread(NULL, 0, thread_m, NULL, 0, NULL);
	if (threadM == NULL) return GetLastError();
	WaitForSingleObject(threadM, INFINITE);						//join with ended thread M


	//CLOSE DA ALL

	CloseHandle(threadA);
	CloseHandle(threadB);
	CloseHandle(threadC);
	CloseHandle(threadD);
	CloseHandle(threadE);
	CloseHandle(threadF);
	CloseHandle(threadG);
	CloseHandle(threadH);
	CloseHandle(threadI);
	CloseHandle(threadK);
	CloseHandle(threadM);

	CloseHandle(SemD);
	CloseHandle(SemE);
	CloseHandle(SemG);
	CloseHandle(SemH);
	CloseHandle(wait_interval);
	CloseHandle(start_interval);
	CloseHandle(Mutex);
	cout << endl;
	system("pause");
	cout << endl;
	return 0;
}
