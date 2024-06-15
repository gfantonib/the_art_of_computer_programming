#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float dk_logarithm(float number, float base);
static float dk_calculate_integer_part(float number, float base);
static float dk_return_x_zero(float number, float base, float integer_part);
static float dk_calculate_float_part(float x_zero);
static float binary_array_to_float(int binary_array[], int len);

int main (void)
{
	float	number;
	float	base;
	float	result;

	number = 2;
	base = 10;
	result = dk_logarithm(number, base);
	printf("log %f base %f = %f\n", number, base, result);
	return (0);
}

static float dk_logarithm(float number, float base)
{
	float result;
	float integer_part;
	float x_zero;
	float float_part;

	integer_part = dk_calculate_integer_part(number, base);
	if (integer_part == -1)
	{
		printf("dk_find_integer_part error!");
		exit(1);
	}
	x_zero = dk_return_x_zero(number, base, integer_part);
	float_part = dk_calculate_float_part(x_zero);
	result = integer_part + float_part;
	return (result);
}

static float dk_calculate_integer_part(float number, float base)
{
	float integer_part;
	float x_zero;

	integer_part = 0;
	while (integer_part < number) // the limit can be slower
	{
		x_zero = number / pow(base, integer_part);
		if (x_zero >= 1 && x_zero < 10)
			return (integer_part);
		integer_part++;
	}
	return (-1);
}

static float dk_return_x_zero(float number, float base, float integer_part)
{
	int x_zero;

	x_zero = number / pow(base, integer_part);
	return (x_zero);
}

static float dk_calculate_float_part(float x_zero)
{
	float x_curr;
	float x_prev;
	float x_prev_squared;
	float float_part;
	int precision;
	int i;

	precision = 10;
	int binary_array[precision];
	x_prev = x_zero;
	i = 0;
	while (i < precision)
	{
		x_prev_squared = pow(x_prev, 2);
		if (x_prev_squared < 10)
		{
			x_curr = pow(x_prev, 2);
			binary_array[i] = 0;
			// printf("%fzero\n", binary_array[i]);
			// printf("%fzero\n", x_curr);
		}
		else if (x_prev_squared >= 10)
		{
			x_curr = pow(x_prev, 2) / 10;
			binary_array[i] = 1;
			// printf("%fone\n", binary_array[i]);
			// printf("%fone\n", x_curr);
		}
		x_prev = x_curr;
		i++;
	}
	float_part = binary_array_to_float(binary_array, precision);
	// printf("%f\n", float_part);
	return (float_part);
}

static float binary_array_to_float(int binary_array[], int len)
{
	float float_part;
	int i;

	float_part = 0;
	i = 0;
	while (i < len)
	{
		float_part += binary_array[i] * pow(2, len -i -1);
		i++;
	}
	i = 10;
	while (float_part > 1)
	{
		float_part = float_part / i;
		i = i * 10;
	}
	return (float_part);
}

