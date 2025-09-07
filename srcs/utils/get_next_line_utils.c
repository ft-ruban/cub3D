#include "utils.h"

void	*ft_calloc(size_t element_count, size_t element_size)
{
	char	*ptr;
	size_t	i;
	size_t	total_size;

	total_size = element_count * element_size;
	i = 0;
	ptr = malloc(total_size);
	if (ptr == 0)
		return (NULL);
	while (i != total_size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}