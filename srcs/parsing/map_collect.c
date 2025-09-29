#include "parsing.h"
#include "utils.h"

// We go to the map first line.
// Until we copied all our map, we allocate the current line_index with the
// result of get_next_line

//LDEV: c:17 ça n'as pas sa place | ATTENTION CAR LINE DEPEND DE CA
//LDEV: c:35 ça nous semble useless (va check quand meme dans le doute!!!) car je peux me gourrer

static bool	copy_the_map(t_settings *set, size_t map_height, int fd)
{
	char	*line;
	size_t	line_index;

	line = NULL;
	line_index = 0;
	if (find_map_first_line(set, &line, fd))
		return (RETURN_FAILURE);
	while (line_index < map_height)
	{
		set->map[line_index] = ft_strdup(line);
		free (line);
		if (!set->map[line_index])
		{
			close (fd);
			return (error_handler(set, MAL_ERR_SET, "map_collect:23 ", MSG_11));
		}
		line_index++;
		line = get_next_line(fd);
		if (!line && line_index < map_height)
			return (error_handler(set, MAL_ERR_SET, "map_collect:28 ", MSG_9));
	}
	free(line);
	if (is_all_map_copied(set, line_index, map_height, fd))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// Close then reopen fd to start the reading of the file from the beginning,
// skip the 6 parameters and stop when finding something different than a '\n'

//LDEV : ligne 49-53 pas de msg d'erreur
//LDEV : mettre un read avant while

static int	read_until_map_start(char *file, t_settings *set, int fd)
{
	char	*path;
	int		new_fd;

	close(fd);
	path = ft_strjoin(MAP_FOLDER_PATH, file);
	if (!path)
		return (MALLOC_ERR);
	new_fd = open(path, O_RDONLY);
	free(path);
	if (new_fd == -1)
		return (OPEN_FAILED);
	if (skip_elements(set, new_fd))
		return (RETURN_FAILURE);
	while (set->buff[0] == '\n')
	{
		printf("proutzor\n");
		if (read(new_fd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "map_collect.c.c:55 ", MSG_6));
	}
		
	return (new_fd);
}

// allocate the suffiscient height memory, the individual lines will be
// allocated later when copying the map
static bool	malloc_map_height(t_settings *set, size_t map_height)
{
	size_t	i;

	i = 0;
	set->map = malloc(sizeof(char *) * (map_height + 1));
	if (!set->map)
		return (error_handler(set, MAL_ERR_SET, "map_collect.c.c:68 ", MSG_1));
	set->map[map_height] = NULL;
	return (RETURN_SUCCESS);
}

// We read the map one character at a time, line by line, to know the largest 
// line (width) and the height that increase each time we cross a '\n'
// We know we are out of the map if read = 0 or when we cross two '\n' together
static bool	find_map_size(t_settings *set, size_t *map_height, int fd)
{
	bool	in_map;

	in_map = true;
	if (find_map_start(set, fd))
		return (RETURN_FAILURE);
	while (in_map == true)
	{
		if (parse_map_line(set, fd, &in_map))
			return (RETURN_FAILURE);
		if (read(fd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "map_collect.c.c:88 ", MSG_6));
		if (set->buff[0] == '\n')
			in_map = false;
		(*map_height)++;
	}
	map_height--;
	return (RETURN_SUCCESS);
}

// We find the map height to then malloc it properly
// We read with a new fd from the beginning of the map
// we copy the map
bool	map_collect(t_settings *set, char *file, int fd)
{
	size_t	map_height;

	map_height = 0;
	if (find_map_size(set, &map_height, fd))
		return (RETURN_FAILURE);
	if (malloc_map_height(set, map_height))
		return (RETURN_FAILURE);
	fd = read_until_map_start(file, set, fd);
	if (fd == OPEN_FAILED || fd == MALLOC_ERR)
		return (RETURN_FAILURE);
	if (copy_the_map(set, map_height, fd))
		return (RETURN_FAILURE);
	print_map(set);
	return (RETURN_SUCCESS);
}
