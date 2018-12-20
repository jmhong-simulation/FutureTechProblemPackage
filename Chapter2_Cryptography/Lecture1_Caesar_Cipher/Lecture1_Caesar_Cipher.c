#include <stdio.h>

#define MAX_STR 64

const int key = 3;

char orignal_message[MAX_STR];
char encrypted[MAX_STR];
char decrypted[MAX_STR];

void encrypt()
{
	for (int i = 0; i < MAX_STR; ++i)
	{
		if (orignal_message[i] == '\0') {
			encrypted[i] = '\0';
			break;
		}

		int ascii = (int)orignal_message[i];
		int ascii_en = ascii - key;

		if (ascii_en < 'a') ascii_en += 'z' - 'a' + 1;

		encrypted[i] = (char)ascii_en;
	}
}

void decrypt()
{
	for (int i = 0; i < MAX_STR; ++i)
	{
		if (encrypted[i] == '\0') {
			decrypted[i] = '\0';
			break;
		}

		int ascii = (int)encrypted[i];
		int ascii_de = ascii + key;

		if (ascii_de > 'z') ascii_de -= 'z' - 'a' + 1;

		decrypted[i] = (char)ascii_de;
	}
}

int main()
{
	printf("Input an original message : ");
	scanf_s("%s", orignal_message, sizeof(orignal_message));

	encrypt();
	
	printf("%s\n", encrypted);

	decrypt();

	printf("%s\n", decrypted);
}

