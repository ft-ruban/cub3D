/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:21:11 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 10:53:24 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// we check if the user entered 1 param and nothing more.
// we check if the param is a .cub to make sure it is the right extension
// we open file to collect the elements above the map
// then we collect and parse the map to match what is required project
// then we setup the texture struct

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
