#include "parsing.h"
#include "utils.h"

//Trouver pk si la map finie par EOF, on infinite loop PAS ICI DANS FIND_MAP_SIZE
static bool	copy_the_map(t_settings *set, char **map, size_t map_height, int fd)
{
    char	*line;
    size_t	line_index;
	
	line = NULL;
    line_index = 0;
	if (find_map_first_line(set, &line, fd))
		return (RETURN_FAILURE);
	while (line_index < map_height)
	{
        map[line_index] = ft_strdup(line);
		free (line);
		if (!map[line_index])
		{
			free_map(map, line_index-1);
			close (fd);
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:32", MSG_11));
		}
        line_index++;
		line = get_next_line(fd);
        if (!line && line_index < map_height)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	}
    if (is_all_map_copied(set, line_index, map_height, fd))
    		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

//LDEV: TODO (JE DOIS MOI FAIRE UN DEFINE DE SCENE_DESCRIPTION)

static int	read_until_map_start(char *file, t_settings *set, int fd)
{
    char	*path;
    int		new_fd;
	char	*line;

    close(fd);
	line = NULL;
    path = ft_strjoin("scene_descriptions/", file);
    if(!path)
		return(MALLOC_ERR);
	new_fd = open(path, O_RDONLY);
    free(path);
    if (new_fd == -1)
        	return (OPEN_FAILED);
	if (skip_elements(set, line, new_fd))
		return (RETURN_FAILURE);
    while (set->buff[0] == '\n')
		if (read(new_fd, set->buff, 1) == -1)
			return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
    return (new_fd);
}

static bool	malloc_map(t_settings *set, int map_width, int map_height)
{
    int i;

    i = 0;
    set->map = malloc(sizeof(char*) * (map_height + 1));
    if (!set->map)
        return(error_handler(set, MAL_ERR_SET, "get_the_map.c:79", MSG_1));
    while (i < map_height)
    {
        set->map[i] = malloc(sizeof(char) * (map_width + 1));
        if (!set->map[i])
        {
            free_map(set->map, i);
            return(error_handler(set, MAL_ERR_SET, "get_the_map.c:87", MSG_1));
        }
		ft_bzero(set->map[i], (map_width + 1));
        i++;
    }
	set->map[map_height] = NULL;
    return (RETURN_SUCCESS);
}

// reading the map one character at a time, line by line, to know the largest line (width)
// and the height that increase each time we cross a '\n'
// We know we are out of the map if read = 0 or when we cross twoo '\n' together
static bool	find_map_size(t_settings *set, size_t *map_width, size_t *map_height, int fd)
{
    bool	in_map;
    size_t	width_counter;

    width_counter = 0;
    in_map = true;
    if (find_map_start(set, fd))
		return (RETURN_FAILURE);
    while(in_map == true)
    {
        if (parse_map_line(set, fd, &in_map, &width_counter))
			return (RETURN_FAILURE);
        if (read(fd, set->buff, 1) == -1)
            return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
        if (set->buff[0] == '\n')
            in_map = false;
        update_map_size(&width_counter, map_width, map_height);
    }
    map_height--;
    return (RETURN_SUCCESS);
}

bool get_the_map(t_settings *set, char *file, int fd)
{
    size_t map_width;
    size_t map_height;

    map_width = 0;
    map_height = 0;
    if (find_map_size(set, &map_width, &map_height, fd))
        	return (RETURN_FAILURE);
	if (malloc_map(set, map_width, map_height))
        return (RETURN_FAILURE);
	fd = read_until_map_start(file, set, fd);
	if (fd == OPEN_FAILED || fd == MALLOC_ERR)
        return (RETURN_FAILURE);
	if (copy_the_map(set, set->map, map_height, fd))
		return (RETURN_FAILURE);
    print_map(set);
    return (RETURN_SUCCESS);
}
