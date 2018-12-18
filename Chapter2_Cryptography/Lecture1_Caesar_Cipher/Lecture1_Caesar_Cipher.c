#include <stdio.h>

#define MAX_STR 255
//const int MAX_STR = 255;

const int key = 3;


void encrypt(const char input_string[], char encrypted_string[])
{
	for (int i = 0; i < MAX_STR; ++i)
	{
		char c = input_string[i];

		if (c == '\0') break;

		int ascii = (int)c;
		int ascii_en = ascii - key;

		if (ascii_en < 'a') ascii_en += 'z' - 'a' + 1;
		else if (ascii_en > 'z') ascii_en -= 'z' - 'a' + 1;

		char c_en = (char)ascii_en;

		encrypted_string[i] = c_en;
	}
}

void decrypt(const char encrypted_string[], char decrypted_string[])
{
	for (int i = 0; i < MAX_STR; ++i)
	{
		char c = encrypted_string[i];

		if (c == '\0') break;

		int ascii = (int)c;
		int ascii_dec = ascii + key;

		if (ascii_dec < 'a') ascii_dec += 'z' - 'a' + 1;
		else if (ascii_dec > 'z') ascii_dec -= 'z' - 'a' + 1;

		char c_dec = (char)ascii_dec;

		decrypted_string[i] = c_dec;
	}
}

int main()
{
	char input_string[MAX_STR];
	char encrypted_string[MAX_STR] = { 0, };
	char decrypted_string[MAX_STR] = { 0, };

	//scanf("%s", input_string);
	scanf_s("%s", input_string, sizeof(input_string));
	printf("Original = %s\n", input_string);

	encrypt(input_string, encrypted_string);

	printf("Encrypted = %s\n", encrypted_string);

	decrypt(encrypted_string, decrypted_string);

	printf("Decrypted = %s\n", decrypted_string);

	printf("END\n");
}

