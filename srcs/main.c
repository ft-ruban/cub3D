/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:02:31 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 21:08:41 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1) we init our cub3d structure, and give a default value for error_type.
// 2) parsing part.
// 3) init_exec_struct handle the textures, mlx and ray setups.
// 4) init the data related to the "player".
// 5) hook_and_loop to setup the loop that will make the program loop during
// 	  execution until the user exit the program by choice.
// 6) Once the loops passed, use clean and exit to cleanup datas before exit.

int	main(int argc, char *argv[])
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (error_handler(NULL, CUB_SET_FAIL, "(main:28) ", MSG_1));
	cub3d->error_type = ALL_OK;
	if (parsing(argc, argv, cub3d))
		return (clean_and_exit(cub3d));
	if (init_exec_struct(cub3d))
		return (clean_and_exit(cub3d));
	init_player_data(cub3d);
	cub3d->print = true;
	hook_and_loop(cub3d, cub3d->mlx);
	return (clean_and_exit(cub3d));
}
