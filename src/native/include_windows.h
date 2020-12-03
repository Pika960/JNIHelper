#ifndef INCLUDE_WINDOWS_H
#define INCLUDE_WINDOWS_H

//includes
#include <conio.h>
#include <jni.h>
#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#include <lmcons.h>

//defines
#ifdef _MSC_VER
    #define getPressedCharacter() _getch()
#else
    #define getPressedCharacter() getch()
#endif

//prototypes
char* decToHex(int number);
HKEY  convertStringToHKEY(JNIEnv* env, jstring hkey);
int   generateNewColorCode(WORD currentConsoleAttr, WORD newConsoleAttr);
int   hexToDec(char* str1);
LONG  deleteRegKey(HKEY hkey, LPCSTR lpSubKey);
LONG  deleteRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
LONG  setRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD dwData);
LONG  setRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, LPCSTR lpData);
void  flushBuffers();
void  getRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, char& pvData);
void  getRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD& pvData);

#endif
