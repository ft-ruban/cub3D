#include "parsing.h"
#include "utils.h"

static int is_all_map_copied(t_settings *set, int i, int height, int fd)
{
	printf("i: %d, height: %d\n", i, height);
    if (i != height)
    {
        free_map(set->map, i);
        close(fd);
        return(error_handler(set, MAL_ERR_SET, "get_the_map.c:10", MSG_1));
    }
	return (RETURN_SUCCESS);
}

//LDEV: check msg d'erreur pas forcement coherant
//LDEV: 

//Trouver pk si la map finie par EOF, on infinite loop PAS ICI DANS FIND_MAP_SIZE
int cpy_the_map(t_settings *set, char **map, int height, int fd)
{
    char    *line;
    int     i;
	
    i = 0;
	line = get_next_line(fd); //TODO PROTECT
	while (line[0] == '\n')
	{
		line = get_next_line(fd);
        if (!line)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_1));
	}
	while (i < height)
	{

        map[i] = ft_strdup(line);
		free (line);
		if (!map[i])
		{
			free_map(map, i-1);
			close (fd);
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:32", MSG_1));
		}
        i++;
		if (i < height)
			line = get_next_line(fd);
        if (!line)
			return(error_handler(set, MAL_ERR_SET, "get_the_map.c:36", MSG_1));
	}
    if (is_all_map_copied(set, i, height, fd))
    		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

//LDEV: TODO (JE DOIS MOI FAIRE UN DEFINE DE SCENE_DESCRIPTION)
//LDEV: faire un define de -1 pour dire que -1 = erreur
//LDEV: PENSER a free path
//LDEV: protect notre get_next_line
//LDEV: 6 tu peux en faire un include
//LDEV: voir pour mettre i a 0

int read_until_map_start(char *file, t_settings *set, int fd)
{
    char *path;
    int new_fd;
    int i;
	char *line;

    i = 1;
    close(fd);
    path = ft_strjoin("scene_descriptions/", file); //MAP_FOLDER_PATH
    if(!path)
        return(-1);
    new_fd = open(path, O_RDONLY);
    if (new_fd == -1)
        return (RETURN_FAILURE);
    while (i <= 6)
    {
        read(new_fd, set->buff, 1);
        if (set->buff[0] != '\n')
        {
            line = get_next_line(new_fd);
            i++;
        }
    }
    while (set->buff[0] == '\n')
        	read(fd, set->buff, 1);
    return (new_fd);
}

//LDEV : a propos du w et h :>
//LDEV : ça peut etre bien de mettre l'assignement juste apres la declaration de i
//LDEV : triple ptr char ***map?
//LDEV : suspect pour nos gros soucis de segault blabaltruc

int malloc_map(t_settings *set, int w, int h, char ***map)
{
    int i;

    *map = malloc(sizeof(int) * h + 1);
    if (!*map)
        return(error_handler(set, MAL_ERR_SET, "get_the_map.c:79", MSG_1));
    i = 0;
    while (i <= h)
    {
        (*map)[i] = malloc(sizeof(char) * w);
        if (!(*map)[i])
        {
            free_map(*map, i);
            return(error_handler(set, MAL_ERR_SET, "get_the_map.c:87", MSG_1));
        }
        i++;
    }
	(*map)[h+1] = NULL;
    return (ALL_OK);
}

//LDEV: TODO histoire chiante de PTR map width
//LDEV: TODO transformer en BOOL
//LDEV: TODO? update size plutot que update width height
//LDEV: SOUCIS QUAND DERNIERE LIGNE POSSEDE LE EOF

int find_map_size(t_settings *set, int *map_width_max, int *map_height, int fd)
{
    bool    in_map;
    int     map_width;
//    int     result_read;

    map_width = 0;
    in_map = true;
    if (find_map_start(set, fd))
		return (RETURN_FAILURE);
    while(in_map == true)
    {
        while(set->buff[0] != '\n') // Lire jusqu'à la prochaine ligne
        {
            if (read(fd, set->buff, 1) == -1)
                return(error_handler(set, INV_READ, "get_the_map.c:111", MSG_6));
            map_width++;
        }
        if (read(fd, set->buff, 1) == -1) // Lire le prochain charactère et check si 2 '\n' à la suite
            return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
        if (set->buff[0] == '\n')
            in_map = false;
        update_width_height(&map_width, map_width_max, map_height);
    }
    map_height--; // il s'est incrémenté une fois de trop et je voulais pas le faire commencer à '-1'
    return (RETURN_SUCCESS);
}

//