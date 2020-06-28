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
		ReleaseSemaphore(SemE, 1, nullptr);
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
		ReleaseSemaphore(SemG, 1, nullptr);
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
		ReleaseSemaphore(SemH, 1, nullptr);
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
		ReleaseSemaphore(SemD, 1, nullptr);
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
	Mutex = CreateMutex(nullptr, FALSE, nullptr);
	

	if (Mutex == nullptr)
	{		
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}

	SemD = CreateSemaphore(nullptr, 1, 1, nullptr);
	if (SemD == nullptr)
	{
		cout << "CreateSemaphore error: SemD" << GetLastError() << endl;
		return 1;
	}

	SemE = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemD == nullptr)
	{
		cout << "CreateSemaphore error: SemE " << GetLastError() << endl;
		return 1;
	}

	SemG = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemD == nullptr)
	{
		cout << "CreateSemaphore error: SemG" << GetLastError() << endl;
		return 1;
	}

	SemH = CreateSemaphore(nullptr, 0, 1, nullptr);
	if (SemD == nullptr)
	{
		cout << "CreateSemaphore error: SemH" << GetLastError() << endl;
		return 1;
	}

	wait_interval = CreateSemaphore(nullptr, 0, 3, nullptr);
	if (wait_interval == nullptr)
	{
		cout << "CreateSemaphore error: wait_interval" << GetLastError() << endl;
		return 1;
	}
	start_interval = CreateSemaphore(nullptr, 0, 3, nullptr);
	if (start_interval == nullptr)
	{
		cout << "CreateSemaphore error: start_interval" << GetLastError() << endl;
		return 1;
	}

	HANDLE threadA, threadB, threadC, threadD, threadE, threadF, threadG, threadH, threadI, threadK, threadM;

	//1-st interval
	threadA = CreateThread(nullptr, 0, thread_a, nullptr, 0, nullptr);
	if (threadA == nullptr) return GetLastError();

	threadC = CreateThread(nullptr, 0, thread_c, nullptr, 0, nullptr);
	if (threadC == nullptr) return GetLastError();

	threadD = CreateThread(nullptr, 0, thread_d, nullptr, 0, nullptr);
	if (threadD == nullptr) return GetLastError();

	threadE = CreateThread(nullptr, 0, thread_e, nullptr, 0, nullptr);
	if (threadE == nullptr) return GetLastError();

	WaitForSingleObject(threadA, INFINITE);                              //join with ended thread A
	WaitForSingleObject(wait_interval, INFINITE);                   //wait for thread C to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread D to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread E to finish

	//2-d interval

	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread C
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread D
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread E

	threadB = CreateThread(nullptr, 0, thread_b, nullptr, 0, nullptr);
	if (threadB == nullptr) return GetLastError();

	WaitForSingleObject(threadC, INFINITE);						//join with ended thread C
	WaitForSingleObject(threadB, INFINITE);						//join with ended thread B
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread D to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread E to finish

	//3-d interval
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread D
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread E


	threadG = CreateThread(nullptr, 0, thread_g, nullptr, 0, nullptr);
	if (threadG == nullptr) return GetLastError();

	threadH = CreateThread(nullptr, 0, thread_h, nullptr, 0, nullptr);
	if (threadH == nullptr) return GetLastError();
	WaitForSingleObject(threadD, INFINITE);						//join with ended thread D
	WaitForSingleObject(wait_interval, INFINITE);                   //wait for thread E to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread G to finish
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread H to finish

	//4-th interval
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread G
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread E
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread H
	threadF = CreateThread(nullptr, 0, thread_f, nullptr, 0, nullptr);
	if (threadF == nullptr) return GetLastError();
	WaitForSingleObject(threadG, INFINITE);						//join with ended thread G
	WaitForSingleObject(threadE, INFINITE);						//join with ended thread E
	WaitForSingleObject(threadF, INFINITE);						//join with ended thread F
	WaitForSingleObject(wait_interval, INFINITE);                 //wait for thread H to finish


	//5-th interval
	ReleaseSemaphore(start_interval, 1, nullptr);            //continue thread H
	threadI = CreateThread(nullptr, 0, thread_i, nullptr, 0, nullptr);
	if (threadI == nullptr) return GetLastError();
	threadK = CreateThread(nullptr, 0, thread_k, nullptr, 0, nullptr);
	if (threadK == nullptr) return GetLastError();
	WaitForSingleObject(threadH, INFINITE);						//join with ended thread H
	WaitForSingleObject(threadI, INFINITE);						//join with ended thread I
	WaitForSingleObject(threadK, INFINITE);						//join with ended thread K

	//6-th interval
	threadM = CreateThread(nullptr, 0, thread_m, nullptr, 0, nullptr);
	if (threadM == nullptr) return GetLastError();
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
	return 0;
}
