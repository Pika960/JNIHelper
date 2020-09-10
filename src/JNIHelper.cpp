//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JNIHelper.h"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <curses.h>
    #include <math.h>
    #include <portaudio.h>
    #include <term.h>
    #include <termios.h>
    #include <unistd.h>
#endif

#ifdef _MSC_VER
    #define getch() _getch()
#endif

#ifdef __linux__
    #define SAMPLE_RATE         44100
    #define FRAMES_PER_BUFFER   512

    struct beep_head;

    typedef float (*beep_waveform)(struct beep_head*);

    typedef struct beep_note
    {
        float amplitude;
        float duration;
        float frequency;
        beep_waveform waveform;
    } beep_note;

    typedef struct beep_head
    {
        int frame;
        beep_note* note;
    } beep_head;
#endif

//helper method for interacting with the console
char getPressedCharacter()
{
    #ifdef _WIN32
    return getch();

    #else
    char           buf = 0;
    struct termios old = {0};

    fflush(stdout);

    if (tcgetattr(0, &old) < 0)
    {
        perror("tcsetattr()");
    }

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
    {
        perror("tcsetattr ICANON");
    }

    if (read(0, &buf, 1) < 0)
    {
        perror("read()");
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
    {
        perror("tcsetattr ~ICANON");
    }

    return buf;
    #endif
}

//helper methods for number conversion (windows only)
#ifdef _WIN32
char* decToHex(int number)
{
    char hexString[20];
    return itoa(number, hexString, 16);
}

int hexToDec(char* str1)
{
    return strtol(str1, NULL, 16);
}

int generateNewColorCode(WORD currentConsoleAttr, WORD newConsoleAttr)
{
    char hexCurrent[3];
    char hexNew[3];

    strncpy(hexCurrent, decToHex(currentConsoleAttr), 3);
    strncpy(hexNew,     decToHex(newConsoleAttr),     3);

    if(strlen(hexCurrent) == 1)
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
#endif

//helper methods for sound generation (linux only)
#ifdef __linux__
void portaudio_initialize()
{
    if(!freopen("/dev/null", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/null\n");
    }

    Pa_Initialize();

    if(!freopen("/dev/tty", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/tty\n");
    }
}

void portaudio_terminate()
{
    if(!freopen("/dev/null", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/null\n");
    }

    Pa_Terminate();

    if(!freopen("/dev/tty", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/tty\n");
    }
}

int beep_head_callback(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags, void *userData)
{
    beep_head* head   = (beep_head*)(userData);
    float*     buffer = (float*)outputBuffer;

    for(int frame = 0; frame < framesPerBuffer; frame++)
    {
        buffer[frame] = head->note->waveform(head);
        head->frame++;
    }

    return paContinue;
}

void beep_note_play(beep_note* note)
{
    beep_head head = {
        .frame = 0,
        .note = note
    };

    PaStream* stream;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE,
        FRAMES_PER_BUFFER, beep_head_callback, &head);
    Pa_StartStream(stream);
    Pa_Sleep(note->duration);
    Pa_AbortStream(stream);
}

float beep_waveform_sine(beep_head *head)
{
   beep_note *note = head->note;
   return note->amplitude * sin(2 * M_PI * note->frequency * head->frame / SAMPLE_RATE);
}
#endif

//core methods
JNIEXPORT void JNICALL Java_JNIHelper_beep(JNIEnv *env, jclass javaClass, jint frequency, jint duration)
{
    #ifdef _WIN32
    Beep(frequency, duration);
    #else
    portaudio_initialize();

    beep_note note = {
       .amplitude = 1.0,
       .duration = (float)duration,
       .frequency = (float)frequency,
       .waveform = beep_waveform_sine
    };

    beep_note_play(&note);
    portaudio_terminate();
    #endif
}

JNIEXPORT void JNICALL Java_JNIHelper_consoleClear(JNIEnv *env, jclass javaClass)
{
    #ifdef _WIN32
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi ))
    {
        return;
    }

    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
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
}

JNIEXPORT void JNICALL Java_JNIHelper_consolePause(JNIEnv *env, jclass javaClass)
{
    char chKey;
    int  numKey;

    printf("%s", "Press any key to continue...");

    chKey  = getPressedCharacter();
    numKey = chKey;

    for(int i = 1; i <= 256; i++)
    {
        if(i == numKey)
        {
            break;
        }
    }

    #ifdef __linux__
    printf("%s", "\n");
    #endif
}

JNIEXPORT void JNICALL Java_JNIHelper_printColoredText(JNIEnv *env, jclass javaClass, jstring str, jint colorCode)
{
    const char *arg = env->GetStringUTFChars(str, NULL);
    
    #ifdef _WIN32
    HANDLE                     hConsole;
    WORD                       currentConsoleAttr;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        currentConsoleAttr = csbi.wAttributes;
    }

    else
    {
        currentConsoleAttr = 0;
    }

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, generateNewColorCode(currentConsoleAttr, colorCode));

    printf("%s", arg);

    FlushConsoleInputBuffer(hConsole);
    SetConsoleTextAttribute(hConsole, currentConsoleAttr);

    #else
    printf("\e[1;%dm%s\e[0m", colorCode, arg);
    #endif
}

JNIEXPORT void JNICALL Java_JNIHelper_sendStringToNative(JNIEnv *env, jclass javaClass, jstring str)
{
    const char *arg = env->GetStringUTFChars(str, NULL);
    
    system(arg);
}
