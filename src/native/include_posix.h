#ifndef INCLUDE_POSIX_H
#define INCLUDE_POSIX_H

//includes
#include <curses.h>
#include <jni.h>
#include <math.h>
#include <portaudio.h>
#include <pwd.h>
#include <sys/param.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

//defines
#define SAMPLE_RATE       44100
#define FRAMES_PER_BUFFER 512

//structs
struct beep_head;

//typedefs
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
    int        frame;
    beep_note* note;
} beep_head;

//prototypes
char  getPressedCharacter();
float beep_waveform_sine(beep_head* head);
int   beep_head_callback(const void* inputBuffer, void* outputBuffer,
      unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags, void* userData);
void  beep_note_play(beep_note* note);
void  clearInputBuffer();
void  flushBuffers();
void  portaudio_initialize();
void  portaudio_terminate();

#endif
