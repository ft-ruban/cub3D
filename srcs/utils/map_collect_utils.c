#include "parsing.h"

// We know that the elements of the file are valid.
// We read until we find something else than a '\n'.
// we skip it with a get_next_line.
// And so on for the element number of time we have to repeat it.
bool	skip_elements(t_parsing *parsing, int new_fd)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < ELEMENT_NBR)
	{
		if (read(new_fd, parsing->buff, 1) == READ_FAILED)
			return (error_handler(parsing, INV_READ,
					"map_collect_utils.c:16 ", MSG_6));
		if (parsing->buff[0] != '\n')
		{
			line = get_next_line(new_fd);
			if (!line)
				return (error_handler(parsing, MAL_ERR_SET,
						"map_collect_utils.c:22 ", MSG_9));
			free(line);
			i++;
		}
	}
	return (RETURN_SUCCESS);
}

// We browse through the entire line until we find a '\n'
// If we reach the end of the file, we are no longer in the map
bool	parse_map_line(t_parsing *parsing, int fd, bool *in_map)
{
	int	result_read;

	result_read = 0;
	while (parsing->buff[0] != '\n')
	{
		result_read = read(fd, parsing->buff, 1);
		if (result_read == READ_FAILED)
			return (error_handler(parsing, INV_READ, "get_the_map.c:41 ", MSG_6));
		if (result_read == END_OF_FILE)
		{
			*in_map = false;
			break ;
		}
	}
	return (RETURN_SUCCESS);
}

// We check if the next line is just a '\n'
// We stop when we find anything else
bool	find_map_first_line(t_parsing *parsing, char **line, int fd)
{
	*line = get_next_line(fd);
	if (!*line)
		return (error_handler(parsing, MAL_ERR_SET, "get_the_map.c:58 ", MSG_9));
	while (*line[0] == '\n')
	{
		free(*line);
		*line = get_next_line(fd);
		if (!*line)
			return (error_handler(parsing, MAL_ERR_SET,
					"get_the_map.c:64 ", MSG_9));
	}
	return (RETURN_SUCCESS);
}
