#include<stdio.h>
#include<math.h>
double func(double x)
{
	return x * x*x*x - 3 * x*x*x + 1.5*x*x - 4.0;
}
double dfunc(double x)
{
	return 4 * x*x*x - 9 * x*x + 3 * x;
}
int NewtonMethod(double *x, int maxcyc, double precision)
{
	double x0, x1;
	int i;
	x0 = *x;
	i = 0;
	while (i < maxcyc)
	{
		if (dfunc(x0) == 0.0)
		{
			printf("导数为零\n");
			return 0;
		}
		x1 = x0 - func(x0) / dfunc(x0);
		if (fabs(x1 - x0) < precision || fabs(func(x1)) < precision)
		{
			*x = x1;
			return 1;
		}
		else
		{
			x0 = x1;
		}
		i++;
	}
	printf("未达到精度");
	return 0;
}
int main()
{
	double x, precision;
	int maxcyc, result;
	x = 2.0;
	maxcyc = 1000;
	precision = 0.00001;
	result = NewtonMethod(&x, maxcyc, precision);
	if (result == 1)
	{
		printf("%lf", x);
	}
	else
	{
		printf("fail");
	}
	return 0;
}