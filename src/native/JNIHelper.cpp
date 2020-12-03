//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JNIHelper.h"

#ifdef _WIN32
    #include "include_windows.h"
#else
    #include "include_posix.h"
#endif

//core methods
JNIEXPORT jboolean JNICALL Java_JNIHelper_deleteRegistryKey(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return JNI_FALSE;
    }

    else
    {
        LPCSTR lpSubKey = (LPCSTR)env->GetStringUTFChars(subkey, NULL);

        LONG result = deleteRegKey(rootKey, lpSubKey);

        env->ReleaseStringUTFChars(subkey, lpSubKey);

        if (result != ERROR_SUCCESS)
        {
            return JNI_FALSE;
        }

        return JNI_TRUE;
    }
    #else
    return JNI_FALSE;
    #endif
}

JNIEXPORT jboolean JNICALL Java_JNIHelper_deleteRegistryValue(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey, jstring value)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return JNI_FALSE;
    }

    else
    {
        LPCSTR lpSubKey = (LPCSTR)env->GetStringUTFChars(subkey, NULL);
        LPCSTR lpValue  = (LPCSTR)env->GetStringUTFChars(value,  NULL);

        LONG result = deleteRegValue(rootKey, lpSubKey, lpValue);

        env->ReleaseStringUTFChars(subkey, lpSubKey);
        env->ReleaseStringUTFChars(value,  lpValue);

        if (result != ERROR_SUCCESS)
        {
            return JNI_FALSE;
        }

        return JNI_TRUE;
    }
    #else
    return JNI_FALSE;
    #endif
}

JNIEXPORT jboolean JNICALL Java_JNIHelper_isElevated(JNIEnv* env,
    jclass javaClass)
{
    jboolean isElevated = JNI_FALSE;

    #ifdef _WIN32
    HANDLE hToken;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        DWORD           cbSize;
        TOKEN_ELEVATION elevation;

        cbSize = sizeof(TOKEN_ELEVATION);

        if (GetTokenInformation(hToken, TokenElevation, &elevation,
            sizeof(elevation), &cbSize))
        {
            isElevated = elevation.TokenIsElevated;
        }

        if(hToken)
        {
            CloseHandle(hToken);
        }
    }
    #else
    if (geteuid() == 0)
    {
        isElevated = JNI_TRUE;
    }
    #endif

    return isElevated;
}

JNIEXPORT jboolean JNICALL Java_JNIHelper_isHeadless(JNIEnv* env,
    jclass javaClass)
{
    jboolean isHeadless = JNI_FALSE;

    #ifdef _WIN32
    DISPLAY_DEVICE displayDevice;
    DWORD          displayIndex = 0;

    displayDevice.cb = sizeof(DISPLAY_DEVICE);

    if (!EnumDisplayDevices(NULL, displayIndex, &displayDevice, 0))
    {
        isHeadless = JNI_TRUE;
    }
    #else
    if (NULL == getenv("DISPLAY"))
    {
        isHeadless = JNI_TRUE;
    }
    #endif

    return isHeadless;
}

JNIEXPORT jboolean JNICALL Java_JNIHelper_setRegistryValueNumeric(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey, jstring value, jint data)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return JNI_FALSE;
    }

    else
    {
        if (data < 0)
        {
            data = 0;
        }

        LPCSTR lpSubKey = (LPCSTR)env->GetStringUTFChars(subkey, NULL);
        LPCSTR lpValue  = (LPCSTR)env->GetStringUTFChars(value,  NULL);

        LONG result = setRegValue(rootKey, lpSubKey, lpValue, data);

        env->ReleaseStringUTFChars(subkey, lpSubKey);
        env->ReleaseStringUTFChars(value,  lpValue);

        if (result != ERROR_SUCCESS)
        {
            return JNI_FALSE;
        }

        return JNI_TRUE;
    }
    #else
    return JNI_FALSE;
    #endif
}

JNIEXPORT jboolean JNICALL Java_JNIHelper_setRegistryValueText(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey, jstring value,
    jstring data)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return JNI_FALSE;
    }

    else
    {
        LPCSTR lpSubKey = (LPCSTR)env->GetStringUTFChars(subkey, NULL);
        LPCSTR lpValue  = (LPCSTR)env->GetStringUTFChars(value,  NULL);
        LPCSTR lpData   = (LPCSTR)env->GetStringUTFChars(data,   NULL);

        LONG result = setRegValue(rootKey, lpSubKey, lpValue, lpData);

        env->ReleaseStringUTFChars(subkey, lpSubKey);
        env->ReleaseStringUTFChars(value,  lpValue);
        env->ReleaseStringUTFChars(data,   lpData);

        if (result != ERROR_SUCCESS)
        {
            return JNI_FALSE;
        }

        return JNI_TRUE;
    }
    #else
    return JNI_FALSE;
    #endif
}

JNIEXPORT jdouble JNICALL Java_JNIHelper_getSystemMemoryInfo(JNIEnv* env,
    jclass javaClass, jstring type, jstring unitMode, jboolean round)
{
    const char* t  = env->GetStringUTFChars(type, NULL);
    const char* um = env->GetStringUTFChars(unitMode, NULL);

    double  divider          = 0;
    jdouble systemMemoryInfo = 0;

    if (strcmp("mb", um) == 0)
    {
        divider = 1024 * 1024;
    }

    else if (strcmp("gb", um) == 0)
    {
        divider = 1024 * 1024 * 1024;
    }

    else
    {
        divider = 1024;
    }

    #ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    if (strcmp("available", t) == 0)
    {
        systemMemoryInfo = (statex.ullAvailPhys / divider);
    }

    else
    {
        systemMemoryInfo = (statex.ullTotalPhys / divider);
    }
    #else
    unsigned long long page_size  = 0;
    unsigned long long pages_phys = 0;

    if (strcmp("available", t) == 0)
    {
        page_size  = sysconf(_SC_PAGESIZE);
        pages_phys = sysconf(_SC_AVPHYS_PAGES);
    }

    else
    {
        page_size  = sysconf(_SC_PAGE_SIZE);
        pages_phys = sysconf(_SC_PHYS_PAGES);
    }

    systemMemoryInfo = (page_size * pages_phys) / divider;
    #endif

    if (round == JNI_TRUE)
    {
        systemMemoryInfo = (int)(systemMemoryInfo * 100 + 0.5);
        return (jdouble)(systemMemoryInfo / 100);
    }

    env->ReleaseStringUTFChars(type, t);
    env->ReleaseStringUTFChars(unitMode, um);

    return systemMemoryInfo;
}

JNIEXPORT jint JNICALL Java_JNIHelper_getRegistryValueNumeric(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey, jstring value)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return -1;
    }

    else
    {
        DWORD  pvData   = 0;
        LPCSTR lpSubKey = (LPCSTR)env->GetStringUTFChars(subkey, NULL);
        LPCSTR lpValue  = (LPCSTR)env->GetStringUTFChars(value,  NULL);

        getRegValue(rootKey, lpSubKey, lpValue, pvData);

        env->ReleaseStringUTFChars(subkey, lpSubKey);
        env->ReleaseStringUTFChars(value,  lpValue);

        if (pvData == INT_MAX)
        {
            return -1;
        }

        return pvData;
    }
    #else
    return -1;
    #endif
}

JNIEXPORT jstring JNICALL Java_JNIHelper_getComputerName(JNIEnv* env,
    jclass javaClass)
{
    #ifdef _WIN32
    char    computerName [MAX_COMPUTERNAME_LENGTH + 1];
    wchar_t computerNameW[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD   size = sizeof(computerNameW) / sizeof(computerNameW[0]);

    if (GetComputerNameW(computerNameW, &size) == 0)
    {
        return env->NewStringUTF("Undefined");
    }

    wcstombs(computerName, computerNameW, (MAX_COMPUTERNAME_LENGTH + 1));
    #else
    char computerName[MAXHOSTNAMELEN + 1];

    if (gethostname(computerName, MAXHOSTNAMELEN) != 0)
    {
        return env->NewStringUTF("Undefined");
    }
    #endif

    return env->NewStringUTF(computerName);
}

JNIEXPORT jstring JNICALL Java_JNIHelper_getOperatingSystemName(JNIEnv* env,
    jclass javaClass)
{
    char operatingSystemName[256];

    #if defined (_AIX)
    strcpy(operatingSystemName, "AIX");
    #elif defined (BSD)
    strcpy(operatingSystemName, "BSD");
    #elif defined (__hpux)
    strcpy(operatingSystemName, "HP-UX");
    #elif defined (__linux__)
    strcpy(operatingSystemName, "Linux");
    #elif defined (__APPLE__) && defined (__MACH__)
    strcpy(operatingSystemName, "macOS");
    #elif defined(__sun) && defined(__SVR4)
    strcpy(operatingSystemName, "Solaris");
    #elif defined(__unix__)
    strcpy(operatingSystemName, "UNIX");
    #elif defined (_WIN32) || defined (_WIN64)
    strcpy(operatingSystemName, "Windows");
    #else
    strcpy(operatingSystemName, "Unsupported");
    #endif

    return env->NewStringUTF(operatingSystemName);
}

JNIEXPORT jstring JNICALL Java_JNIHelper_getRegistryValueText(JNIEnv* env,
    jclass javaClass, jstring hkey, jstring subkey, jstring value)
{
    #ifdef _WIN32
    HKEY rootKey = convertStringToHKEY(env, hkey);

    if (rootKey == NULL)
    {
        return env->NewStringUTF("Undefined");
    }

    else
    {
        char   pvData[256] = {};
        LPCSTR lpSubKey    = (LPCSTR)env->GetStringUTFChars(subkey, NULL);
        LPCSTR lpValue     = (LPCSTR)env->GetStringUTFChars(value,  NULL);

        getRegValue(rootKey, lpSubKey, lpValue, *pvData);

        env->ReleaseStringUTFChars(subkey, lpSubKey);
        env->ReleaseStringUTFChars(value,  lpValue);

        return env->NewStringUTF(pvData);
    }
    #else
    return env->NewStringUTF("Undefined");
    #endif
}

JNIEXPORT jstring JNICALL Java_JNIHelper_getUserName(JNIEnv* env,
    jclass javaClass)
{
    #ifdef _WIN32
    char    userName [UNLEN + 1];
    wchar_t userNameW[UNLEN + 1];
    DWORD   size = sizeof(userNameW) / sizeof(userNameW[0]);

    if (GetUserNameW(userNameW, &size) == 0)
    {
        return env->NewStringUTF("Undefined");
    }

    wcstombs(userName, userNameW, (UNLEN + 1));
    #else
    char*  userName;
    struct passwd *pw;
    uid_t  uid;

    uid = geteuid();
    pw  = getpwuid(uid);

    if (pw)
    {
        userName = pw->pw_name;
    }

    else
    {
        userName = (char*)"Undefined";
    }
    #endif

    return env->NewStringUTF(userName);
}

JNIEXPORT void JNICALL Java_JNIHelper_beep(JNIEnv* env, jclass javaClass,
    jint frequency, jint duration)
{
    #ifdef _WIN32
    Beep(frequency, duration);
    #else
    portaudio_initialize();

    beep_note note = {
       .amplitude  = 1.0,
       .duration   = (float)duration,
       .frequency  = (float)frequency,
       .waveform   = beep_waveform_sine
    };

    beep_note_play(&note);
    portaudio_terminate();
    #endif
}

JNIEXPORT void JNICALL Java_JNIHelper_consoleClear(JNIEnv* env,
    jclass javaClass)
{
    flushBuffers();

    #ifdef _WIN32
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        return;
    }

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount,
        homeCoords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount,
        homeCoords, &count))
    {
        return;
    }

    SetConsoleCursorPosition(hStdOut, homeCoords);

    #else
    if (!cur_term)
    {
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);

        if (result <= 0)
        {
            return;
        }
    }

    putp(tigetstr("clear"));
    #endif

    flushBuffers();
}

JNIEXPORT void JNICALL Java_JNIHelper_consolePause(JNIEnv* env,
    jclass javaClass)
{
    flushBuffers();

    char chKey;
    int  numKey;

    printf("%s", "Press any key to continue...");

    chKey  = getPressedCharacter();
    numKey = chKey;

    for (int i = 1; i <= 256; i++)
    {
        if (i == numKey)
        {
            break;
        }
    }

    #ifndef _WIN32
    printf("%s", "\n");
    #endif

    flushBuffers();
}

JNIEXPORT void JNICALL Java_JNIHelper_printColoredText(JNIEnv* env,
    jclass javaClass, jstring str, jint colorCode)
{
    flushBuffers();

    const char* arg = env->GetStringUTFChars(str, NULL);

    #ifdef _WIN32
    HANDLE                     hConsole;
    WORD                       currentConsoleAttr;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        currentConsoleAttr = csbi.wAttributes;
    }

    else
    {
        currentConsoleAttr = 0;
    }

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole,
        generateNewColorCode(currentConsoleAttr, colorCode));

    printf("%s", arg);

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, currentConsoleAttr);

    #else
    printf("\e[1;%dm%s\e[0m", colorCode, arg);
    #endif

    env->ReleaseStringUTFChars(str, arg);

    flushBuffers();
}

JNIEXPORT void JNICALL Java_JNIHelper_sendStringToNative(JNIEnv* env,
    jclass javaClass, jstring str)
{
    const char* arg = env->GetStringUTFChars(str, NULL);

    system(arg);

    env->ReleaseStringUTFChars(str, arg);
}
