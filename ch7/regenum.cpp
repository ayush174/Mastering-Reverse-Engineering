// regenum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

#pragma warning(disable:4996)

int main()
{
	LPCSTR lpSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkResult;
	DWORD dwIndex;
	char ValueName[1024];
	char ValueData[1024];
	DWORD cchValueName;
	DWORD result;
	DWORD dType;
	DWORD dataSize;
	HKEY hKey = HKEY_LOCAL_MACHINE;

	if (RegOpenKeyExA(hKey, lpSubKey, 0, KEY_READ, &hkResult) == ERROR_SUCCESS)
	{
		printf("HKEY_LOCAL_MACHINE\\%s\n", lpSubKey);
		dwIndex = 0;
		result = ERROR_SUCCESS;
		while (result == ERROR_SUCCESS)
		{
			cchValueName = 1024;
			result = RegEnumValueA(hkResult, dwIndex, (char *)&ValueName, &cchValueName, NULL, NULL, NULL, NULL);
			if (result == ERROR_SUCCESS)
			{
				RegQueryValueExA(hkResult, ValueName, NULL, &dType, (unsigned char *)&ValueData, &dataSize);
				if (strlen(ValueName) == 0)
					sprintf((char*)&ValueName, "%s", "(Default)");
				printf("%s: %s\n", ValueName, ValueData);
			}
			dwIndex++;
		}
		RegCloseKey(hkResult);
	}
    return 0;
}

