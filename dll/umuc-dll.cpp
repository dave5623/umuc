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
