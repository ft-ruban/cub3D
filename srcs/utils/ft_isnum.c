
#include "utils.h"

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (RETURN_SUCCESS);
	else
		return (RETURN_FAILURE);
}