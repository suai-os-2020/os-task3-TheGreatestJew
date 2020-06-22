#include "lab3.h"
#include <windows.h>
#include <stdio.h>

using namespace std;

#define THREADCOUNT 5

HANDLE Thread[THREADCOUNT];

HANDLE Mutex;

HANDLE SemD, SemE, SemG, SemH; // SemD, SemE, SemG, SemH are for DEGH  SemH1, SemI, SemK are for  HIK interval 

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


DWORD WINAPI threads_unsynchronized(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_d(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemD, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemE, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_e(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemE, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemG, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_g(LPVOID text)

{

	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemG, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemH, 1, NULL);
	}
	return 0;
}

DWORD WINAPI thread_h(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemH, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemD, 1, NULL);
	}


	return 0;
}




int lab3_init()

{
	DWORD ThreadID;
	Mutex = CreateMutex(NULL, FALSE, NULL);
	int count = 0;

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


	char const* textsCADE[] = { "c", "a", "d", "e" };

	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsCADE[i], 0, &ThreadID);

		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsCADE[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsCBDE[] = { "c", "b", "d", "e" };

	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsCBDE[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsCBDE[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsDEGH[] = { "d", "e", "g", "h" };
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, (void*)textsDEGH[0], 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error: " << textsDEGH[0] << GetLastError() << endl;
		return 1;
	}

	Thread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, (void*)textsDEGH[1], 0, &ThreadID);
	if (Thread[1] == NULL)
	{
		cout << "CreateThread error: " << textsDEGH[1] << GetLastError() << endl;
		return 1;
	}

	Thread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, (void*)textsDEGH[2], 0, &ThreadID);
	if (Thread[2] == NULL)
	{
		cout << "CreateThread error: " << textsDEGH[2] << GetLastError() << endl;
		return 1;
	}

	Thread[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, (void*)textsDEGH[3], 0, &ThreadID);
	if (Thread[3] == NULL)
	{
		cout << "CreateThread error: " << textsDEGH[3] << GetLastError() << endl;
		return 1;
	}

	for (int i = 0; i < 3; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsHFEG[] = { "e", "f", "g", "h" };
	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsHFEG[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsHFEG[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsHIK[] = { "h", "i", "k" };
	for (int i = 0; i < 3; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsHIK[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsHIK[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;


	char const* textsM = "m";
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsM, 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error: " << textsM << GetLastError() << endl;
		return 1;
	}

	WaitForSingleObject(Thread[0], INFINITE);
	for (int i = 0; i < THREADCOUNT; ++i) {
		CloseHandle(Thread[i]);
	}

	CloseHandle(SemD);
	CloseHandle(SemE);
	CloseHandle(SemG);
	CloseHandle(SemH);
	CloseHandle(Mutex);
	cout << endl;
	return 0;
}
