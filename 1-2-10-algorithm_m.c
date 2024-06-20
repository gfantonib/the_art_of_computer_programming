#include <stdio.h>

int	function(int var);
int	dk_find_maximum(int (*function)(int), int n);

int main(void)
{
	int	n;
	int	maximum;

	n = 5;
	maximum = dk_find_maximum(function, n);
	printf("maximum: %d\n", maximum);
	return (0);
}

int	function(int var)
{
	int result;

	result = var * -1;
	return (result);
}

int	dk_find_maximum(int (*function)(int), int n)
{
	int k;
	int dominus;
	int	functus;

	dominus = n;
	k = n - 1;
	functus = function(n);
	while (k > 0)
	{
		if (function(k) > functus)
		{
			dominus = k;
			functus = function(k);
		}
		k--;
	}
	return (dominus);
}