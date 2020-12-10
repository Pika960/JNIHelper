//includes
#include "include_windows.h"

/**
 * converts a decimal to a hexadecimal number
 * @param number the decimal number
 * @return the hexadecimal number
 */
char* decToHex(int number)
{
    char hexString[20];
    return itoa(number, hexString, 16);
}

/**
 * converts a string to the corresponding HKEY
 * @param env a pointer to the JNI environment
 * @param hkey the name of a handle to an open registry key
 * @return the corresponding HKEY
 */
HKEY convertStringToHKEY(JNIEnv* env, jstring hkey)
{
    const char* hkeyName = env->GetStringUTFChars(hkey, NULL);

    HKEY rootKey;

    if (strcmp("HKEY_CLASSES_ROOT", hkeyName) == 0)
    {
        rootKey = HKEY_CLASSES_ROOT;
    }

    else if (strcmp("HKEY_CURRENT_CONFIG", hkeyName) == 0)
    {
        rootKey = HKEY_CURRENT_CONFIG;
    }

    else if (strcmp("HKEY_CURRENT_USER", hkeyName) == 0)
    {
        rootKey = HKEY_CURRENT_USER;
    }

    else if (strcmp("HKEY_LOCAL_MACHINE", hkeyName) == 0)
    {
        rootKey = HKEY_LOCAL_MACHINE;
    }

    else if (strcmp("HKEY_USERS", hkeyName) == 0)
    {
        rootKey = HKEY_USERS;
    }

    else
    {
        rootKey = NULL;
    }

    env->ReleaseStringUTFChars(hkey, hkeyName);

    return rootKey;
}

/**
 * generates a new color code based on the existing configuration
 * @param currentConsoleAttr the current attribute configuration
 * @param newConsoleAttr the new attribute configuration
 * @return the new color code
 */
int generateNewColorCode(WORD currentConsoleAttr, WORD newConsoleAttr)
{
    char hexCurrent[3];
    char hexNew[3];

    strncpy(hexCurrent, decToHex(currentConsoleAttr), 2);
    strncpy(hexNew,     decToHex(newConsoleAttr),     2);

    if (strlen(hexCurrent) == 1)
    {
        hexCurrent[0] = hexNew[0];
        hexCurrent[1] = hexNew[1];
    }

    else
    {
        hexCurrent[1] = hexNew[0];
    }

    return hexToDec(hexCurrent);
}

/**
 * converts a hexadecimal to a decimal number
 * @param str the hexadecimal number
 * @return the decimal number
 */
int hexToDec(char* str)
{
    return strtol(str, NULL, 16);
}

/**
 * deletes a registry key
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @return ERROR_SUCCESS if successful, otherwise the specific error code
 */
LONG deleteRegKey(HKEY hkey, LPCSTR lpSubKey)
{
    HKEY regKey;
    LONG resDelete = RegDeleteKey(hkey, lpSubKey);

    if (resDelete == ERROR_SUCCESS)
    {
        return resDelete;
    }

    LONG resOpen = RegOpenKeyEx(hkey, lpSubKey, 0, KEY_READ, &regKey);

    if (resOpen != ERROR_SUCCESS)
    {
        if (resOpen == ERROR_FILE_NOT_FOUND)
        {
            return ERROR_SUCCESS;
        }

        else
        {
            return resOpen;
        }
    }

    LONG resClose = RegCloseKey(regKey);

    if (resClose != ERROR_SUCCESS)
    {
        return resClose;
    }

    return ERROR_SUCCESS;
}

/**
 * deletes a registry value
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @param lpValue the name of the value
 * @return ERROR_SUCCESS if successful, otherwise the specific error code
 */
LONG deleteRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue)
{
    HKEY regKey;
    LONG resDelete;

    #if (_WIN32_WINNT >= 0x0600)
    resDelete = RegDeleteKeyValue(hkey, lpSubKey, lpValue);

    if (resDelete == ERROR_SUCCESS)
    {
        return resDelete;
    }
    #else
    resDelete = ERROR_NOT_SUPPORTED;
    #endif

    LONG resOpen = RegOpenKeyEx(hkey, lpSubKey, 0, KEY_SET_VALUE, &regKey);

    if (resOpen != ERROR_SUCCESS)
    {
        if (resOpen == ERROR_FILE_NOT_FOUND)
        {
            return ERROR_SUCCESS;
        }

        else
        {
            return resOpen;
        }
    }

    if (resDelete == ERROR_NOT_SUPPORTED)
    {
        resDelete = RegDeleteValue(regKey, lpValue);

        if (resDelete != ERROR_SUCCESS)
        {
            return resDelete;
        }
    }

    LONG resClose = RegCloseKey(regKey);

    if (resClose != ERROR_SUCCESS)
    {
        return resClose;
    }

    return ERROR_SUCCESS;
}

/**
 * creates/sets a registry value (numeric)
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @param lpValue the name of the value
 * @param dwData the data of the value
 * @return ERROR_SUCCESS if successful, otherwise the specific error code
 */
LONG setRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD dwData)
{
    HKEY regKey;
    LONG resOpen = RegOpenKeyEx(hkey, lpSubKey, 0, KEY_ALL_ACCESS , &regKey);

    if (resOpen != ERROR_SUCCESS)
    {
        if (resOpen == ERROR_FILE_NOT_FOUND)
        {
            RegCreateKeyEx(hkey, lpSubKey, NULL, NULL,
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &regKey, NULL);
        }

        else
        {
            return resOpen;
        }
    }

    LONG resSet = RegSetValueEx(regKey, lpValue, 0, REG_DWORD,
        (LPBYTE)&dwData, sizeof(dwData));

    if (resSet != ERROR_SUCCESS)
    {
        return resSet;
    }

    LONG resClose = RegCloseKey(regKey);

    if (resClose != ERROR_SUCCESS)
    {
        return resClose;
    }

    return ERROR_SUCCESS;
}

/**
 * creates/sets a registry value (text)
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @param lpValue the name of the value
 * @param lpData the data of the value
 * @return ERROR_SUCCESS if successful, otherwise the specific error code
 */
LONG setRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, LPCSTR lpData)
{
    HKEY regKey;
    LONG resOpen = RegOpenKeyEx(hkey, lpSubKey, 0, KEY_ALL_ACCESS , &regKey);

    if (resOpen != ERROR_SUCCESS)
    {
        if (resOpen == ERROR_FILE_NOT_FOUND)
        {
            RegCreateKeyEx(hkey, lpSubKey, NULL, NULL,
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &regKey, NULL);
        }

        else
        {
            return resOpen;
        }
    }

    LONG resSet = RegSetValueEx(regKey, lpValue, 0, REG_SZ,
        (LPBYTE)lpData, _tcslen(lpData) * sizeof(TCHAR));

    if (resSet != ERROR_SUCCESS)
    {
        return resSet;
    }

    LONG resClose = RegCloseKey(regKey);

    if (resClose != ERROR_SUCCESS)
    {
        return resClose;
    }

    return ERROR_SUCCESS;
}

/**
 * flushes the input and output buffer
 */
void flushBuffers()
{
    fflush(stdout);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

/**
 * gets a registry value (text)
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @param lpValue the name of the value
 * @param pvData the reference where the requested data will be stored
 */
void getRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, char& pvData)
{
    DWORD pcbData = 256;
    LONG  resGet  = RegGetValue(hkey, lpSubKey, lpValue, RRF_RT_ANY, NULL,
        (PVOID)&pvData, &pcbData);

    if (resGet != ERROR_SUCCESS)
    {
        strcpy(&pvData, "Undefined");
    }
}

/**
 * gets a registry value (numeric)
 * @param hkey a handle to an open registry key
 * @param lpSubKey the path of a registry key relative to the hkey parameter
 * @param lpValue the name of the value
 * @param pvData the reference where the requested data will be stored
 */
void getRegValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD& pvData)
{
    DWORD pcbData = sizeof(DWORD);
    LONG  resGet  = RegGetValue(hkey, lpSubKey, lpValue, RRF_RT_ANY, NULL,
        (PVOID)&pvData, &pcbData);

    if (resGet != ERROR_SUCCESS)
    {
        pvData = INT_MAX;
    }
}
