/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/23 10:19:40 by ldevoude         ###   ########.fr       */
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
	
	if(return_value >= 17)
	{
		free_map(cub3d->map);	
	}
	if(return_value >= 15)
	{
		free(cub3d->map->map);
	}
	if(return_value >= 13)
	{
		free(cub3d->map);	
	}
	if(return_value >= 5)
	{
		free(cub3d->parsing);	
	}
	if(return_value >= 2)
	{
		free(cub3d);
	}
	return (return_value);
}
