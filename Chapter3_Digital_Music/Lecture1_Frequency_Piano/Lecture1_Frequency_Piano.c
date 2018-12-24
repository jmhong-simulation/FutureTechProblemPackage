#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

//#define NUM_NOTES 3
//char key_table[NUM_NOTES] = { 'a', 's', 'd' };
//unsigned long freq_table[NUM_NOTES] = { (unsigned long)261.6256 , 294ul , (unsigned long)329.6276 };

char * key_table = NULL;
unsigned long * freq_table = NULL;

int num_notes = 0;

unsigned long find_freq(const char key)
{
	for (int k = 0; k < num_notes; ++k)
	{
		if (key == key_table[k]) return freq_table[k];
	}

	return 0;
}

int main()
{
	// read key-freq from a script file
	FILE *file = fopen("key_table.txt", "r");

	int num_keys;
	fscanf(file, "%d\n", &num_keys);

	num_notes = num_keys;

	key_table = (char*)malloc(sizeof(char) * num_keys);
	freq_table = (unsigned long*)malloc(sizeof(unsigned long)*num_keys);

	for (int k = 0; k < num_keys; ++k)
	{
		char key;
		double freq;
		fscanf(file, "%c %lf\n", &key, &freq);
		printf("%c %f\n", key, freq);

		// initialize key-freq table
		key_table[k] = key;
		freq_table[k] = (unsigned long)freq;
	}

	fclose(file);

	while (1)
	{
		const char key = _getch();
		printf("You pressed %c key\n", (char)key);
		if (key == 27) break;

		const unsigned long freq = find_freq(key);

		if (freq == 0) printf("Undefined key %c\n", key);
		else
			Beep(freq, 500);
	}
	
	
	/*Beep(293.6638, 500);

	Beep(329.6276, 500);*/

	Sleep(1000);

	free(key_table);
	free(freq_table);
}