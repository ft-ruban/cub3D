#include "parsing.h"

// Here we check if the file sent do possess the right
//.cub extension by checking the last characters in the
// given string of char

static bool	is_file_cub_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (false);
	return (true);
}

static bool	init_parsing_struct(t_cub3d *cub3d)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (RETURN_FAILURE);
	cub3d->parsing = parsing;
	parsing->buff = NULL;
	parsing->rp_no = NULL;
	parsing->rp_so = NULL;
	parsing->rp_we = NULL;
	parsing->rp_ea = NULL;
	parsing->ceil_r = NONE_ASSIGNED;
	parsing->ceil_g = NONE_ASSIGNED;
	parsing->ceil_b = NONE_ASSIGNED;
	parsing->floor_r = NONE_ASSIGNED;
	parsing->floor_g = NONE_ASSIGNED;
	parsing->floor_b = NONE_ASSIGNED;
	return (RETURN_SUCCESS);
}

// static void convert_rgb_hex(t_parsing *parsing, t_texture *texture)
// {

// }

static void texture_struct_setup(t_cub3d *cub3d)
{
	t_texture *texture;

	texture = malloc (sizeof(t_texture));
	if (!texture)
		return(RETURN_FAILURE);
	//convert_rgb_hex(cub3d->parsing);	
}

// we check if the user entered 1 param and nothing more.
// we check if the param is a .cub to make sure it is the right extension
// we open file to collect the elements above the map
// TODO we parse the map and save its content inside of a variable(s)
// TODO if in the end parsing can only end up in two ways, turn it into a bool

// TODO msg error dans cub3d plutot ca serais mieux je pense.
// je vais rentrer et je reprend demain c'est un peu difficile avec le chat

int	parsing_init(int argc, char *argv[], t_cub3d *cub3d)
{
	int		fd;
	t_map	*map_info;

	if (argc != 2)
		return (error_handler(cub3d, PAR_NBR_ARGC, "parsing.c:TOFILL ", MSG_2));
	if (!is_file_cub_extension(argv[1]))
		return (error_handler(cub3d, PAR_EXTENSION, "parsing.c:TOFILL ",
				MSG_3));
	if (init_parsing_struct(cub3d))
		return (error_handler(cub3d, PARSING_INIT_FAIL, "parsing.c:TOFILL ",
				MSG_17));
	if (prepare_collect_elements(argv[1], cub3d, &fd, &cub3d->parsing->buff))
		return (RETURN_FAILURE);
	map_info = malloc(sizeof(t_map));
	if (!map_info)
		return (error_handler(cub3d, 42, "main:TOFILL ", MSG_1)); // tocomplete
	cub3d->map = map_info;
	if (get_and_check_map(argv[1], cub3d, fd, map_info))
	{
		free(map_info);
		return (RETURN_FAILURE);
	}
	texture_struct_setup(cub3d);
	return (RETURN_SUCCESS);
}
