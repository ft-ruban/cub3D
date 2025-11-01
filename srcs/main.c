/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:02:31 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 14:02:37 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// WIP DOC : we init our cub3d structure, then we parse the
// arguments + content of the file in (parsing) before handling the initiation
// of the textures (and store the necessary data related to the textures of the
// project then come the init of hook_andloop that would lead to the loop/hook
// that handle event and interaction with our project before AND during the exec

// TODO last 1 leak (the ray things)

int	main(int argc, char *argv[])
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (error_handler(NULL, CUB_SET_FAIL, "main:TOFILL ", MSG_1));
	cub3d->error_type = ALL_OK;
	cub3d->print = true;
	if (parsing_init(argc, argv, cub3d))
		return (clean_and_exit(cub3d));
	if (init_mlx_texture_img(cub3d))
		return (clean_and_exit(cub3d));
	hook_and_loop(cub3d, cub3d->mlx);
	return (clean_and_exit(cub3d));
	return (0);
}
