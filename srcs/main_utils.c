/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/29 20:40:01 by maballet         ###   ########lyon.fr   */
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
	
	// if(return_value >= 26 || return_value == ALL_OK)
	// {
	// 	free(cub3d->texture->no);
	// 	free(cub3d->texture->so);
	// 	free(cub3d->texture->ea);
	// 	free(cub3d->texture->we);
	// }
	if(return_value >= 25|| return_value == ALL_OK)
	{
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
