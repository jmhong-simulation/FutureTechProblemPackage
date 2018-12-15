#include <stdio.h>

int main()
{
	double annual_salary = 0.3;

	int start_age = 25, retire_age = 60;
	double salary_inc = 0.03;

	printf("Input your first annual salary = ");
	scanf_s("%lf", &annual_salary);

	printf("Input your start age and retirement age = ");
	scanf_s("%d %d", &start_age, &retire_age);

	printf("Input your annual salary increase rate = ");
	scanf_s("%lf", &salary_inc);

	double total_income = 0.0;
	double salary_sum = 0.0;

	FILE *file = fopen("income_history.txt", "w");

	for (int age = start_age; age <= retire_age; ++age)
	{
		if (age == 55) annual_salary *= 0.5;

		printf("Age = %d, annual salary = %f\n", age, annual_salary);

		total_income += annual_salary * (1.0 - 0.3);
		salary_sum += annual_salary;

		fprintf(file, "%f %f\n", annual_salary, total_income);

		if (age <= 53) annual_salary *= (1.0 + salary_inc);
	}

	const double ave_ann_sal = salary_sum / ((double)retire_age - start_age + 1);
	const double annuity = ave_ann_sal * 0.45;

	for (int age = retire_age + 1; age <= 100; ++age)
	{
		total_income += annuity;

		printf("Age = %d, annual salary = %f\n", age, annuity);
		fprintf(file, "%f %f\n", annuity, total_income);
	}

	printf("Total income = %f\n", total_income);

	fclose(file);
}
