#include "parsing.h"

void       update_map_size(size_t *map_width, size_t *map_width_max, size_t *map_height)
{
	(*map_height)++;
	if (*map_width > *map_width_max)
		*map_width_max = *map_width;
	*map_width = 0;
}

bool	skip_elements(t_settings *set, char *line, int new_fd)
{
	size_t	i;

	i = 0;
	while (i < ELEMENT_NBR)
    {
        read(new_fd, set->buff, 1);
        if (set->buff[0] != '\n')
        {
            line = get_next_line(new_fd);
            if (!line)
				return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
            i++;
        }
    }
	return (RETURN_SUCCESS);
}

bool	parse_map_line(t_settings *set, int fd, bool *in_map, size_t *width_counter)
{
	int	result_read;

	result_read = 0;
	while(set->buff[0] != '\n')
	{
		result_read = read(fd, set->buff, 1);
		if (result_read == -1)
			return(error_handler(set, INV_READ, "get_the_map.c:111", MSG_6));
		if (result_read == 0)
		{
			*in_map = false;
			break;
		}
		(*width_counter)++;
	}
	return (RETURN_SUCCESS);
}

bool	find_map_first_line(t_settings *set, char **line, int fd)
{
	*line = get_next_line(fd);
    if (!*line)
	    return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	while (*line[0] == '\n')
	{
		*line = get_next_line(fd);
        if (!*line)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	}
	return (RETURN_SUCCESS);
}
