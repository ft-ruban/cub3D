#include "parsing.h"
#include "utils.h"

// We go to the map first line.
// Until we copied all our map, we allocate the current line_index with the
// result of get_next_line
static bool	copy_the_map(t_parsing *parsing, size_t map_height, int fd, t_map *map_info)
{
	char	*line;
	size_t	line_index;

	line = NULL;
	line_index = 0;
	if (find_map_first_line(parsing, &line, fd))
		return (RETURN_FAILURE);
	while (line_index < map_height)
	{
		map_info->map[line_index] = ft_strdup(line);
		free (line);
		if (!map_info->map[line_index])
		{
			close (fd);
			return (error_handler(parsing, MAL_ERR_SET, "map_collect:23 ", MSG_11));
		}
		line_index++;
		line = get_next_line(fd);
		if (!line && line_index < map_height)
			return (error_handler(parsing, MAL_ERR_SET, "map_collect:28 ", MSG_9));
	}
	free(line);
	return (RETURN_SUCCESS);
}

// Close then reopen fd to start the reading of the file from the beginning,
// skip the 6 parameters and stop.
static int	reopen_file_and_skip_elements(char *file, t_parsing *parsing, int fd)
{
	char	*path;
	int		new_fd;

	close(fd);
	path = ft_strjoin(MAP_FOLDER_PATH, file);
	if (!path)
	{
		error_handler(parsing, MAL_ERR_SET, "map_collect.c.c:45 ", MSG_1);
		return (MALLOC_ERR);
	}
	new_fd = open(path, O_RDONLY);
	free(path);
	if (new_fd == OPEN_FAILED)
		return (OPEN_FAILED);
	if (skip_elements(parsing, new_fd))
		return (READ_OR_MALLOC_ERR);
	return (new_fd);
}

// allocate the suffiscient height memory, the individual lines will be
// allocated later when copying the map.
static bool	malloc_map_height(t_settings *set, size_t map_height, t_map *map_info)
{
	size_t	i;

	i = 0;
	map_info->map = malloc(sizeof(char *) * (map_height + 1));
	if (!map_info->map)
		return (error_handler(set, MAL_ERR_SET, "map_collect.c.c:66 ", MSG_1));
	map_info->map[map_height] = NULL;
	return (RETURN_SUCCESS);
}

// We read the map one character at a time, line by line, to know the largest 
// line (width) and the height that increase each time we cross a '\n'
// We know we are out of the map if read = 0 or when we cross two '\n' together
static bool	find_map_size(t_parsing *parsing, size_t *map_height, int fd)
{
	bool	in_map;

	in_map = true;
	if (find_map_start(parsing, fd))
		return (RETURN_FAILURE);
	while (in_map == true)
	{
		if (parse_map_line(parsing, fd, &in_map))
			return (RETURN_FAILURE);
		if (read(fd, parsing->buff, 1) == READ_FAILED)
			return (error_handler(parsing, INV_READ, "map_collect.c.c:86 ", MSG_6));
		if (parsing->buff[0] == '\n')
			in_map = false;
		(*map_height)++;
	}
	map_height--;
	return (RETURN_SUCCESS);
}

// We find the map height to then malloc it properly
// We read with a new fd from the beginning of the map
// we copy the map
bool	map_collect(t_parsing *parsing, t_map *map_info, char *file, int fd)
{
	size_t	map_height;

	map_height = 0;
	if (find_map_size(parsing, &map_height, fd))
		return (RETURN_FAILURE);
	if (malloc_map_height(parsing, map_height, map_info))
		return (RETURN_FAILURE);
	fd = reopen_file_and_skip_elements(file, parsing, fd);
	if (fd == OPEN_FAILED || fd == MALLOC_ERR)
		return (RETURN_FAILURE);
	if (copy_the_map(parsing, map_height, fd, map_info))
		return (RETURN_FAILURE);
	print_map(map_info);
	return (RETURN_SUCCESS);
}
