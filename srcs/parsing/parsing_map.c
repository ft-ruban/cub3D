
#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

int closed_check(char **map)
{
        int i;
    int j;

    j = 0;
    while (map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
            {
                if (map[j][i -1] == '\0' || map[j][i +1] == '\0'
					|| map[j -1][i] == '\0' || map[j +1][i] == '\0')
                	return (RETURN_FAILURE);
            }
            i++;
        }
        j++;
    }
    return (RETURN_SUCCESS);
}

bool	character_is_valid(char c)
{
	if (c != '1' && c != '0' && c != 'N'
    	&& c != 'S' && c != 'E' && c != 'W'
    	&& c != '\0')
    	return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

int element_check(char **map)
{
    int i;
    int j;
    bool player;

    j = 0;
    while (map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == 'N' && map[j][i] == 'S'
                && map[j][i] == 'E' && map[j][i] == 'W')
            {
                if (player == true)
                    return (RETURN_FAILURE);
                else
                    player = true;
            }
            if (character_is_invalid(map[j][i]))
                return (RETURN_FAILURE);
            i++;
        }
        j++;
    }
    return (RETURN_SUCCESS);
}

void    free_map(char **map, int fail_nbr)
{
    int i;

    i = 0;
    if (fail_nbr)
    {
        while (i > fail_nbr)
        {
            free(map[i]);
            i++;
        }
    }
    else
    {
        while (map[i])
        {
            free(map[i]);
            i++;
        }
    }
}

int get_the_map(char **map, int height, int fd)
{
	char	*tmp;
    char    *line;
    int     i;

	tmp = NULL;
    line = get_next_line(fd);
    i = 0;
	while (i <= height && line != NULL)
	{
		tmp = map;
		if (tmp == NULL)
			map = strdup(line);
		else
			map = ft_strjoin(tmp, line);
		free (line);
		if (tmp != NULL)
			free (tmp);
		if (map == NULL)
		{
			close (fd);
			return (NULL);
		}
		line = get_next_line(fd);
        i++;
	}
    if (i != height)
    {
        free_map(map, NULL);
        return (MALLOC_ERROR_SET);
    }
	return (ALL_OK);
}

int malloc_map(int w, int h, char ***map, int fd)
{
    int i;

    *map = malloc(sizeof(int) * h);
    if (!*map)
        return(MALLOC_ERROR_SET);
    i = 0;
    while ((*map)[i])
    {
        (*map)[i] = malloc(sizeof(char) * w);
        if (!(*map)[i])
        {
            free_map(*map, i);
            return (MALLOC_ERROR_SET);
        }
        i++;
    }
    return (ALL_OK);
}

int collect_check_map(t_settings *set, int fd)
{
    int map_width;
    int map_height;

    find_map_w_and_h(&map_width, &map_height, fd);
    if (malloc_map(map_width, map_height, &(set->map), fd) != ALL_OK)
    {
        set->error_type = MALLOC_ERROR_SET;
        return (RETURN_FAILURE);
    }
 
    get_the_map(set->map, map_height, fd);
    if (element_check(set->map) != ALL_OK)
        return (ERR);
    if (closed_check(set->map) != ALL_OK)
        return (ERR);
    return (ALL_OK);
}
