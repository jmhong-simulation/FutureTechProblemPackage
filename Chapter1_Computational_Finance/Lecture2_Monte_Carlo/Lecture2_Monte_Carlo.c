#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 100; ++i)
	{
		const int random_number = rand();

		printf("%d\n", random_number);
	}

	// you may try more accurate std::random in c++
}

