/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:35:18 by maballet          #+#    #+#             */
/*   Updated: 2025/11/03 21:11:49 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_exec_struct(t_cub3d *cub3d)
{
	t_ray	*ray;

	if (texture_struct_setup(cub3d))
		return (error_handler(cub3d, INIT_TEXTURE_FAIL,
				"(init_exec_struct.c:19) ", MSG_18));
	if (init_mlx_texture_img(cub3d))
		return (RETURN_FAILURE);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (error_handler(cub3d, INIT_RAY_FAIL,
				"(init_exec_struct.c:25) ", MSG_32));
	cub3d->ray = ray;
	return (RETURN_SUCCESS);
}
