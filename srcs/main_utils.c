/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/11 15:24:07 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// We init them at those value for further processing in the parsing
void	init_parsing_struct(t_parsing *parsing, t_cub3d *cub3d)
{
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
	parsing->error_type = RETURN_SUCCESS;
	cub3d->parsing = parsing;
}

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

int	clean_and_exit(t_cub3d *cub3d, t_parsing *parsing)
{
	unsigned char	return_value;

	if(parsing)
	{
		return_value = parsing->error_type;
		printf("\n\nRETURN CODE : %u\n", return_value); // TORM THIS IS DEBBUG LINE
		free_parsing_content(parsing);
		free(parsing);
		free(cub3d);
		return (return_value);
	}

	printf("fail malloc parsing\n");
	free(cub3d);
	return(2); //TODEFINE
}
