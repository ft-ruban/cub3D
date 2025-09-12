
#include  "parsing.h"
#include  "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

int enclosed_check(char **map)
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

bool	character_is_invalid(char c)
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
    int width;
    int height;
    bool player;

    height = 0;
    while (map[height])
    {
        width = 0;
        while(map[height][width])
        {
            if (map[height][width] == 'N' && map[height][width] == 'S'
                && map[height][width] == 'E' && map[height][width] == 'W')
            {
                if (player == true)
                    return (RETURN_FAILURE);
                else
                    player = true;
            }
            if (character_is_invalid(map[height][width]))
                return (RETURN_FAILURE);
            width++;
        }
        height++;
    }
    return (RETURN_SUCCESS);
}

void    free_map(char **map, int line_max)
{
    int i;

    i = 0;
    while (i >= line_max)
    {
        free(map[i]);
        i++;
    }
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*dup;

	i = 0;
	dup = malloc(ft_strlen((char *)s) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < ft_strlen((char *)s))
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// TODO ! remettre le read à avant la lecure de la map,
// actuellement on est a la fin de la map donc j'essaye
// de copier un '\0' :/
int get_the_map(char **map, int height, int fd)
{
    char    *line;
    int     i;

    line = get_next_line(fd);
    printf("%d\n", height);
    i = 0;
	while (i < height)
	{
        printf("%s\n", line);
        map[i] = ft_strdup(line);
		free (line);
		if (!map[i])
		{
            free_map(map, i-1);
			close (fd);
			return (MALLOC_ERROR_SET);
		}
        line = get_next_line(fd);
        if (!line)
            return (MALLOC_ERROR_SET);
        i++;
	}
    if (i != height)
    {
        free_map(map, i);
        close(fd);
        return (MALLOC_ERROR_SET);
    }
	return (ALL_OK);
}

int malloc_map(int w, int h, char ***map)
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

int find_map_size(t_settings *set, int *map_width_max, int *map_height, int fd)
{
    bool    in_map;
    bool    map_error;
    int     map_width;

    map_width = 0;
    map_error = false;
    while(set->buff[0] == '\n') // Si set->buff[0] contenait '\0', on aurait déjà quitté le programme
    {
        if (read(fd, set->buff, 1) == -1)
            return (RETURN_FAILURE);
    }
    in_map = true;
    while(in_map == true)
    {
        while(set->buff[0] != '\n') // Lire jusqu'à la prochaine ligne
        {
            if (read(fd, set->buff, 1) == -1)
                return (RETURN_SUCCESS);
            map_width++;
        }
        if (read(fd, set->buff, 1) == -1) // Lire le prochain charactère et check si 2 '\n' à la suite
            return (RETURN_SUCCESS);
        if (set->buff[0] == '\n')
            in_map = false;
        (*map_height)++;
        if (map_width > *map_width_max)
            *map_width_max = map_width;
        map_width = 0;
    }
    map_height--; // il s'est incrémenté une fois de trop et je voulais pas le faire commencer à '-1'
    while(read(fd, set->buff, 1) != 0) // On va jusqu'au bout du fichier
    {
        if (set->buff[0] != '\n')
            return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}

int read_to_map_start(char *file, t_settings *set, int fd)
{
    char *path;
    int new_fd;
    int i;

    i = 0;
    close(fd);
    path = ft_strjoin("scene_descriptions/", file);
    if(!path)
        return(-1);
    new_fd = open(path, O_RDONLY);
    if (new_fd == -1)
        return (RETURN_FAILURE);
    // printf("test\n");
    while (i <= 6)
    {
        read(new_fd, set->buff, 1);
        if (set->buff[0] != '\n')
        {
            get_next_line(new_fd);
            i++;
        }
    }
    while (set->buff[0] == '\n')
        read(fd, set->buff, 1);
    return (new_fd);
}

int collect_check_map(char *file, t_settings *set, int fd)
{
    int map_width;
    int map_height;

    map_width = 0;
    map_height = 0;
    if (find_map_size(set, &map_width, &map_height, fd) != RETURN_SUCCESS)
        return (RETURN_FAILURE);
    if (malloc_map(map_width, map_height, &(set->map)) != RETURN_SUCCESS)
    {
        set->error_type = MALLOC_ERROR_SET;
        return (RETURN_FAILURE);
    }
    fd = read_to_map_start(file, set, fd);
    if (fd == RETURN_FAILURE)
        return (RETURN_FAILURE);
    printf("test\n");
    if (get_the_map(set->map, map_height, fd) != RETURN_SUCCESS)
        return (RETURN_FAILURE);
    if (element_check(set->map) != RETURN_SUCCESS)
        return (RETURN_FAILURE);
    if (enclosed_check(set->map) != RETURN_SUCCESS)
        return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}
