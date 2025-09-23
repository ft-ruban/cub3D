#include "parsing.h"
#include "utils.h"

//Trouver pk si la map finie par EOF, on infinite loop PAS ICI DANS FIND_MAP_SIZE
static bool	cpy_the_map(t_settings *set, char **map, int map_height, int fd)
{
    char    *line;
    int     line_index;
	
    line_index = 0;
	line = get_next_line(fd);
    if (!line)
	    return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	while (line[0] == '\n')
	{
		line = get_next_line(fd);
        if (!line)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	}
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
		if (line_index < map_height)
			line = get_next_line(fd);
        if (!line)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_9));
	}
    if (is_all_map_copied(set, line_index, map_height, fd))
    		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

//LDEV: TODO (JE DOIS MOI FAIRE UN DEFINE DE SCENE_DESCRIPTION)

static bool	read_until_map_start(char *file, t_settings *set, int fd)
{
    char *path;
    int new_fd;
    int i;
	char *line;

    i = 0;
    close(fd);
    path = ft_strjoin("scene_descriptions/", file);
    if(!path)
		return(READ_OR_MALLOC_ERR);
	new_fd = open(path, O_RDONLY);
    free(path);
    if (new_fd == -1)
        return (READ_OR_MALLOC_ERR);
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
    while (set->buff[0] == '\n')
        	read(fd, set->buff, 1);
    return (new_fd);
}

static bool	malloc_map(t_settings *set, int map_width, int map_height)
{
    int i;

    i = 0;
    set->map = malloc(sizeof(int) * map_height + 1);
    if (!set->map)
        return(error_handler(set, MAL_ERR_SET, "get_the_map.c:79", MSG_1));
    while (i <= map_height)
    {
        set->map[i] = malloc(sizeof(char) * map_width);
        if (!set->map[i])
        {
            free_map(set->map, i);
            return(error_handler(set, MAL_ERR_SET, "get_the_map.c:87", MSG_1));
        }
        i++;
    }
	set->map[map_height+1] = NULL;
    return (RETURN_SUCCESS);
}

static bool	find_map_size(t_settings *set, int *map_width, int *map_height, int fd)
{
    bool    in_map;
    int     width_counter;
	int		result_read;

    width_counter = 0;
    in_map = true;
    if (find_map_start(set, fd))
		return (RETURN_FAILURE);
    while(in_map == true)
    {
        while(set->buff[0] != '\n')
        {
			result_read = read(fd, set->buff, 1);
            if (result_read == -1)
                return(error_handler(set, INV_READ, "get_the_map.c:111", MSG_6));
			if (result_read == 0)
			{
				in_map = false;
				break;
			}
            width_counter++;
        }
        if (read(fd, set->buff, 1) == -1)
            return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
        if (set->buff[0] == '\n')
            in_map = false;
        update_map_size(&width_counter, map_width, map_height);
    }
    map_height--;
    return (RETURN_SUCCESS);
}

//LDEV: TODO Voir si tu peux le mettre dans get_the_map ou changer le nom du fichier en question.
//LDEV: TODO si tes int ne peuvent pas aller dans le neg ne pas hesiter a en faire des size_t :>

int get_the_map(t_settings *set, char *file, int fd)
{
    int map_width;
    int map_height;

    map_width = 0;
    map_height = 0;
    if (find_map_size(set, &map_width, &map_height, fd))
        	return (RETURN_FAILURE);
	if (malloc_map(set, map_width, map_height))
        return (RETURN_FAILURE);
	fd = read_until_map_start(file, set, fd);
	if (fd == READ_OR_MALLOC_ERR)
        return (RETURN_FAILURE);
	if (cpy_the_map(set, set->map, map_height, fd))
		return (RETURN_FAILURE);
	// printf("height: %d, width: %d\n", map_height, map_width);
    return (RETURN_SUCCESS);
}
