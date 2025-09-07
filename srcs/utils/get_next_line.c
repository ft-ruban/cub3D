#include "utils.h"

// clean the line until it meet the \n to it will free sbuff if the file is
// finished, else it will return what is necessary to keep for the next
// use of get_next_line.c
char	*newline_cleaner(char *sbuff)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (sbuff[i] != 0 && sbuff[i] != '\n')
		i++;
	if (!sbuff[i])
	{
		free(sbuff);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(sbuff) - i + 1), sizeof(char));
	if (!temp)
		return (free(sbuff), NULL);
	i++;
	while (sbuff[i] != 0)
	{
		temp[j] = sbuff[i];
		i++;
		j++;
	}
	free(sbuff);
	return (temp);
}
// it transfer the content of sbuff into the string that I plan to return
// in the end of the get_next

char	*fill_returned_line(char *sbuff, char *returned_line)
{
	int	i;

	if (!sbuff || !*sbuff)
		return (NULL);
	i = 0;
	while (sbuff[i] != 0 && sbuff[i] != '\n')
		i++;
	returned_line = ft_calloc((i + 2), (sizeof(char)));
	if (!returned_line)
		return (NULL);
	i = 0;
	while (sbuff[i] != 0 && sbuff[i] != '\n')
	{
		returned_line[i] = sbuff[i];
		i++;
	}
	if (sbuff[i] && sbuff[i] == '\n')
		returned_line[i] = '\n';
	return (returned_line);
}
// explicit name, it merge two strings (sbuff + buff) then it return the merged
// version

char	*merge_then_free(char *dest, char *src)
{
	char	*new_str;

	new_str = ft_strjoin(dest, src);
	if (dest)
		free(dest);
	if (!new_str)
		return (NULL);
	return (new_str);
}
// That function does read the content of the file associated by the FD
// and would continue to do so until the \n is met! then we go to merge
// then free and we return sbuff that should
// contain the old leftover + the new line

char	*read_content_then_stock(int fd, char *sbuff)
{
	char	*buff;
	int		bytes_len;

	if (!sbuff)
		sbuff = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(sbuff), NULL);
	bytes_len = 1;
	while (bytes_len > 0)
	{
		bytes_len = read(fd, buff, BUFFER_SIZE);
		if (bytes_len == -1)
		{
			free (sbuff);
			return (free(buff), NULL);
		}
		buff[bytes_len] = 0;
		sbuff = merge_then_free(sbuff, buff);
		if (!sbuff)
			return (free(buff), NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (free(buff), sbuff);
}

// start of the function,
// it also check in cases of errors init variables tht would be usefull later
// sbuff and returned_line would get the return of the different function
// and in the end sbuff would be cleaned to hold the perfect content
// then we return returned_line that does contain the whole line.

char	*get_next_line(int fd)
{
	static char	*sbuff;
	char		*returned_line;

	returned_line = (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(sbuff);
		sbuff = NULL;
		return (NULL);
	}
	sbuff = read_content_then_stock(fd, sbuff);
	if (!sbuff)
		return (NULL);
	returned_line = fill_returned_line(sbuff, returned_line);
	if (!returned_line)
	{
		free(sbuff);
		sbuff = (NULL);
		return (NULL);
	}
	sbuff = newline_cleaner(sbuff);
	return (returned_line);
}