#include <stdio.h>
#pragma comment (lib, "winmm.lib")
#include <windows.h>
#include <mmsystem.h>

void main()
{
	PlaySound(TEXT("sound_files/27.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	// async vs sync
}
