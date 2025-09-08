#include "utils.h"
#include "stdbool.h"

int	convert_ascii_to_int(int i, const char *nptr, int negative)
{
	long	result;

	result = 0;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		result += nptr[i] - 48;
		if (nptr[i + 1] <= '9' && nptr[i + 1] >= '0')
			result *= 10;
		if (result == 2147483647)
			return (2147483647);
		if (result == 2147483648 && negative == true)
			return (-2147483648);
		i++;
	}
	if (negative == true)
		result *= -1;
	return ((int)result);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	negative;

	negative = false;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative = true;
		i++;
	}
	return (convert_ascii_to_int(i, nptr, negative));
}