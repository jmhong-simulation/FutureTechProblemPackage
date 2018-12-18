#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double get_rand_real(const double min, const double max)
{
	double temp = (double)rand() / (double)RAND_MAX; // temp >= 0.0 && temp <= 1.0
	temp = min + (max - min)*temp; // temp >= min && temp <= max

	return temp;
}

double est_income()
{
	//FILE *of = fopen("annual_salary.txt", "w");

	double annual_salary = 0.3;
	double income_sum = 0;

	for (int age = 25; age < 55; age++)
	{

		income_sum += annual_salary;

		//fprintf(of, "%f\n", annual_salary);

		const double salary_increase = get_rand_real(0.0, 0.06);

		annual_salary *= (1.0 + salary_increase);
	}

	//fclose(of);

	return income_sum;
}

void main()
{
	srand((unsigned int)time(NULL));

	int num_samples = 1;
	for (int i = 0; i < 20; ++i)
	{
		double est_inc = 0.0;

		for (int s = 0; s < num_samples; ++s)
		{
			est_inc += est_income();
		}

		printf("%f\n", (double)est_inc / num_samples);

		num_samples *= 2;
	}

	// 3% -> 14.272625
}

