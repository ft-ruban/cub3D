
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
            if (map[j][i] != '0')
            {
                if (map[j][i -1] == '\0' &&)
                return (ERR);
            }
            i++;
        }
        j++;
    }
    return (ALL_OK);
}

int element_check(char **map)
{
    int i;
    int j;

    j = 0;
    while (map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'N'
                && map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W'
                && map[j][i] != '\0')
                return (ERR);
            i++;
        }
        j++;
    }
    return (ALL_OK);
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
        return (ERR);
    get_the_map(set->map, map_height, fd);
    if (element_check(set->map) != ALL_OK)
        return (ERR);
    if (closed_check(set->map) != ALL_OK)
        return (ERR);
    return (ALL_OK);
}

static int element_found(int fd_sd, t_settings *set, char first_letter, char *buff)
{
    if(read(fd_sd, buff, 1) == -1)
    {
        set->error_type = PARSING_READ_FAILURE;
        return(RETURN_FAILURE);
    }
    if(first_letter == 'N' || first_letter == 'S' || 
        first_letter == 'W' || first_letter == 'E')
    {
        if(is_texture_valid(fd_sd, set, first_letter, buff[0]))
            return(RETURN_FAILURE);
    }
    else
    {
        rgb_thing(fd_sd, set, first_letter, buff[0]);
    }
    return(RETURN_SUCCESS);
}
//that function's goal is to check if all our settings are assigned.
//to exit the loop at collect_elements. the loop is supposed to continue
//until everything got filled
static int are_all_elements_filled(t_settings *set)
{
    if(!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea || set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED ||
        set->floor_b == NONE_ASSIGNED || set->cell_r == NONE_ASSIGNED || set->cell_g == NONE_ASSIGNED || set->cell_b == NONE_ASSIGNED)
            return(RETURN_FAILURE);
    else
        return(RETURN_SUCCESS);
}

//TODO lot of error case, need a function to warn the user with the
//proper message + free potential things like buff for ex

int collect_elements(int fd_sd, t_settings *set)
{
    while(are_all_elements_filled(set))
    {
        if(read(fd_sd, set->buff, 1) == -1) //toprotect
        {
            set->error_type = PARSING_READ_FAILURE;
            return(RETURN_FAILURE); //TODO ERRORHANDLER + FREE here if fail probably bcs EOF reached before getting all the elements
        }
        if (set->buff[0] == 'N' || set->buff[0] == 'S' || set->buff[0] == 'W' || set->buff[0] == 'E' || set->buff[0] == 'F' || set->buff[0] == 'C')
        {
            if(element_found(fd_sd, set, set->buff[0], set->buff))
            {
                return(RETURN_FAILURE);
            }
        }
        else if(set->buff[0] != '\n')
        {
            set->error_type = PARSING_ELEMENT_INVALID_CONTENT;
            return(RETURN_FAILURE);
        }
    }
    if (collect_check_map(set, fd_sd) != ALL_OK)
        return (ERR);
    return(RETURN_SUCCESS);
}
