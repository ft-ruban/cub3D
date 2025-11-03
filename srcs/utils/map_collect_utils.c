/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:01:33 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 19:48:17 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// 1) We know that the elements of the file are valid.
// 		We read until we find something else than a '\n'.
// 		we skip it with a get_next_line.
// 		And so on for the element number of time we have to repeat it.
bool	skip_elements(t_parsing *parsing, int new_fd, t_cub3d *cub3d)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < ELEMENT_NBR)
	{
		if (read(new_fd, parsing->buff, 1) == READ_FAILED)
			return (error_handler(cub3d, FAIL_OPEN_MAP,
					"(map_collect_utils.c:27) ", MSG_6));
		if (parsing->buff[0] != '\n')
		{
			line = get_next_line(new_fd);
			if (!line)
				return (error_handler(cub3d, FAIL_OPEN_MAP,
						"(map_collect_utils.c:33) ", MSG_9));
			free(line);
			i++;
		}
	}
	return (RETURN_SUCCESS);
}

// 1) We browse through the entire line until we find a '\n'
// 		If we reach the end of the file, we are no longer in the map
bool	parse_map_line(t_parsing *parsing, int fd, bool *in_map)
{
	int	result_read;

	result_read = 0;
	while (parsing->buff[0] != '\n')
	{
		result_read = read(fd, parsing->buff, 1);
		if (result_read == READ_FAILED)
			return (RETURN_FAILURE);
		if (result_read == END_OF_FILE)
		{
			*in_map = false;
			break ;
		}
	}
	return (RETURN_SUCCESS);
}

// 1) We check if the next line is just a '\n'
//    We stop when we find anything else as it mean the map is starting at that
//    point.
bool	find_map_first_line(char **line, int fd)
{
	*line = get_next_line(fd);
	if (!*line)
		return (RETURN_FAILURE);
	while (*line[0] == '\n')
	{
		free(*line);
		*line = get_next_line(fd);
		if (!*line)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
