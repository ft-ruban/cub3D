#include "parsing.h"

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*dup;

	i = 0;
	dup = malloc(ft_strlen((char *)s) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < ft_strlen((char *)s))
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}