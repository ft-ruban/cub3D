/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:21:11 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/31 09:56:31 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// initiation of parsing struct and we set everything at NULL or -1 by default

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

// here we convert our rgb into a single usable value that can be read as an hex
// value & 0xff is a AND binary operation to mask the value to only keep the
// lowest 8 bits of each int values between 0 and 255 (in our project)
// it is not that important considering we do not allow values above 255, this
// was made to make that function usable elsewhere for a new project or for
// someone else. << 16 is used so the red goes at
// the highest byte position (16-23)
// << 8 to make it at the middle position for the green value (8-15)
//  blue is not shifted it stays in the lowest byte (0-7)
// the function cannot fail.

static void	convert_rgb_hex(t_parsing *parsing, t_texture *texture)
{
	texture->ceil_hex = ((parsing->ceil_r & 0xff) << 16)
		+ ((parsing->ceil_g & 0xff) << 8) + (parsing->ceil_b & 0xff);
	texture->floor_hex = ((parsing->floor_r & 0xff) << 16)
		+ ((parsing->floor_g & 0xff) << 8) + (parsing->floor_b & 0xff);
}

// here we set our texture struct 
// and convert the rgb value we caught in the file into a hexadecimal value

static bool	texture_struct_setup(t_cub3d *cub3d)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	cub3d->texture = texture;
	if (!texture)
		return (RETURN_FAILURE);
	convert_rgb_hex(cub3d->parsing, texture);
	return (RETURN_SUCCESS);
}

// we check if the user entered 1 param and nothing more.
// we check if the param is a .cub to make sure it is the right extension
// we open file to collect the elements above the map

int	parsing_init(int argc, char *argv[], t_cub3d *cub3d)
{
	int	fd;

	if (argc != 2)
		return (error_handler(cub3d, PAR_NBR_ARGC, "parsing.c:96 ", MSG_2));
	if (!is_file_cub_extension(argv[1]))
		return (error_handler(cub3d, PAR_EXTENSION, "parsing.c:98 ", MSG_3));
	if (init_parsing_struct(cub3d))
		return (error_handler(cub3d, PARSING_INIT_FAIL, "parsing.c:100 ",
				MSG_17));
	if (prepare_collect_elements(argv[1], cub3d, &fd, &cub3d->parsing->buff))
		return (RETURN_FAILURE);
	if (get_and_check_map(argv[1], cub3d, fd))
		return (RETURN_FAILURE);
	if (texture_struct_setup(cub3d))
		return (error_handler(cub3d, INIT_TEXTURE_FAIL, "parsing.c:108 ",
				MSG_18));
	return (RETURN_SUCCESS);
}
