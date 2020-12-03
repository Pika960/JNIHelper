//includes
#include "include_posix.h"

char getPressedCharacter()
{
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
}

float beep_waveform_sine(beep_head* head)
{
    beep_note* note = head->note;
    return note->amplitude * sin(2 * M_PI * note->frequency
        * head->frame / SAMPLE_RATE);
}

int beep_head_callback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags, void* userData)
{
    beep_head* head   = (beep_head*)(userData);
    float*     buffer = (float*)outputBuffer;

    for (int frame = 0; frame < framesPerBuffer; frame++)
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

void clearInputBuffer()
{
    int stdin_copy = dup(STDIN_FILENO);
    tcdrain(stdin_copy);
    tcflush(stdin_copy, TCIFLUSH);
    close(stdin_copy);
}

void flushBuffers()
{
    fflush(stdout);
    clearInputBuffer();
}

void portaudio_initialize()
{
    if (!freopen("/dev/null", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/null\n");
    }

    Pa_Initialize();

    if (!freopen("/dev/tty", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/tty\n");
    }
}

void portaudio_terminate()
{
    if (!freopen("/dev/null", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/null\n");
    }

    Pa_Terminate();

    if (!freopen("/dev/tty", "w", stderr))
    {
        printf("%s", "Failed to redirect stderr to /dev/tty\n");
    }
}
