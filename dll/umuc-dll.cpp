// dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <windows.h>

#define UMUC_DLL_EXPORT
#include "umuc-dll.h"

void showMessage()
{
	MessageBox(0, L"UMUC pwns you", L"UMUC FTW!", MB_OK);
}



//// basic_dll.cpp : Defines the exported functions for the DLL application.
////
//
//#include "stdafx.h"
//#include <windows.h>
//
//#define EXPORT_API
//#include "basic_dll.h"
//
//
//void ExecuteTarget()
//{
//	MessageBox(0, L"You are P0wned", L"Malware X", MB_OK);
//}