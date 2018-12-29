#include <stdio.h>
#pragma comment (lib, "winmm.lib")
#include <windows.h>
#include <mmsystem.h>

void main()
{
	unsigned long time_check = timeGetTime();

	while (1)
	{
		char key = _getch();

		unsigned long current_time = timeGetTime();
		printf("Elapsed time = %i\n", current_time - time_check);
		time_check = current_time;

		PlaySound(TEXT("sound_files/25.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	}
}
