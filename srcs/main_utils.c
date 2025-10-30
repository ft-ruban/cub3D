/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/30 16:18:31 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// free everything in set (may be nice to modify that function to create smth)
// that handle all of our struct maybe?

void	free_parsing_content(t_parsing *parsing)
{
	if (parsing->buff)
		free(parsing->buff);
	if (parsing->rp_no)
		free(parsing->rp_no);
	if (parsing->rp_so)
		free(parsing->rp_so);
	if (parsing->rp_we)
		free(parsing->rp_we);
	if (parsing->rp_ea)
		free(parsing->rp_ea);
	get_next_line(-1); //necessary at the end
}

// call free all and return the error value

int	clean_and_exit(t_cub3d *cub3d)
{
	unsigned char	return_value;
	
	return_value = cub3d->error_type;
	printf("\n\nRETURN CODE : %u\n", return_value); // TORM THIS IS DEBBUG LINE
	
	if(return_value >= 30 || return_value == ALL_OK)
	{
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->ea->img);
		//free(cub3d->texture->ea);
	}

	if(return_value >= 29 || return_value == ALL_OK)
	{
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->we->img);
		//free(cub3d->texture->we);
	}
	if(return_value >= 28 || return_value == ALL_OK)
	{
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->so->img);
		//free(cub3d->texture->so);
	}
	if(return_value >= 27 || return_value == ALL_OK)
	{
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->no->img);
		//free(cub3d->texture->no);
	}
	if(return_value >= 26 || return_value == ALL_OK)
	{
		free(cub3d->texture->no);
		free(cub3d->texture->so);
		free(cub3d->texture->ea);
		free(cub3d->texture->we);
	}
	if(return_value >= 25|| return_value == ALL_OK)
	{
		destroy_free_screen(cub3d->mlx);
		free(cub3d->mlx->screen);
		free(cub3d->mlx);
	}
	if(return_value >= 24 || return_value == ALL_OK)
	{
		free(cub3d->texture);
	}
	if(return_value >= 17 || return_value == ALL_OK)
	{
		free_map(cub3d->map);	
	}
	else if(return_value >= 15 || return_value == ALL_OK)
	{
		free(cub3d->map->map);
		free(cub3d->map);
	}
	else if(return_value >= 13 || return_value == ALL_OK)
	{
		free(cub3d->map);
	}
	if(return_value >= 7 || return_value == ALL_OK)
	{
		//free(cub3d->parsing->buff);
		free_parsing_content(cub3d->parsing);
		// free(cub3d->parsing->rp_no);
		// free(cub3d->parsing->rp_so);
		// free(cub3d->parsing->rp_ea);
		// free(cub3d->parsing->rp_we);
	}
	if(return_value >= 5 || return_value == ALL_OK)
	{
		free(cub3d->parsing);	
	}
	if(return_value >= 2 || return_value == ALL_OK)
	{
		free(cub3d);
	}
	get_next_line(-1);
	return (return_value);
}
