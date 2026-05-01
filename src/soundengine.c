#include "cplaudio.h"
#include "cplthread.h"

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern char* y1cbuf;

void csnd_playsound(const csound snd) {
    PlaySound((LPCSTR)snd, NULL, SND_MEMORY | SND_ASYNC); // crash when RIFF is broken !!
    /*
     * https://pl.wikipedia.org/wiki/WAV
     * Author note:
     *
     * win32 api (mmsystem) ma wbudowany loader i player .WAV, zanim sie dowiedzialem o tym, pisalem, potem cala robota poszla w dupe, glownie dlatego, ze thread postanawial robic memory leak dla zabawy
     * po uzyciu tego kodu co jest i sprawdzeniu ze wszystko dziala stwierdzilem ze chuj mi w dupe, gdyz:
     * - pisalem 3 razy od zera loader WAV.
     * - spedzilem cale noce nad naprawianiem jebanego memory leaku
     * - SIX SEVEM
     *
     */
}