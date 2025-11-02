/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:02:31 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 11:54:28 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1) we init our cub3d structure, and give a default value for the variable in
// 2) parsing part
// 3) init_mlx_texture_img handle the textures and mlx setups before launching
// 4) malloc of our ray struct and init the data related to the "player"
// 5) hook_and_loop to setup the loop that will make the program loop during
// 	  execution until the user exit the program by choice.
// 6) once the loops passed, use clean and exit to cleanup datas before exit

int	main(int argc, char *argv[])
{
	t_cub3d	*cub3d;
	t_ray	*ray;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (error_handler(NULL, CUB_SET_FAIL, "main:29 ", MSG_1));
	cub3d->error_type = ALL_OK;
	cub3d->print = true;
	if (parsing_init(argc, argv, cub3d))
		return (clean_and_exit(cub3d));
	if (init_mlx_texture_img(cub3d))
		return (clean_and_exit(cub3d));
	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		error_handler(cub3d, INIT_RAY_FAIL, "main:38 ", MSG_32);
		return (clean_and_exit(cub3d));
	}
	cub3d->ray = ray;
	init_player_data(cub3d);
	hook_and_loop(cub3d, cub3d->mlx);
	return (clean_and_exit(cub3d));
	return (0);
}
