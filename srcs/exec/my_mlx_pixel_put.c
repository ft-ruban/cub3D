/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:58:38 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 13:58:39 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Save the pixel color in the right place x and y of the mlx->screen we are
// gonna print.
// We don't really need the variable "dst_addr" but it makes it easier to
// understand what is happening here.

void	my_mlx_pixel_put(t_mlx *mlx, unsigned int color, unsigned int x,
														unsigned int y)
{
	char	*dst_addr;

	dst_addr = mlx->screen->addr + (y * mlx->screen->line_length
			+ x * (int)(mlx->screen->bits_per_pixel));
	*(unsigned int *)dst_addr = color;
}
