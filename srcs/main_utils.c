/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/14 10:35:37 by maballet         ###   ########lyon.fr   */
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

int	clean_and_exit(t_cub3d *cub3d, t_parsing *parsing)
{
	unsigned char	return_value;

	return_value = cub3d->error_type;
	printf("\n\nRETURN CODE : %u\n", return_value); // TORM THIS IS DEBBUG LINE
	if(return_value <= BEFORE_PARSING_INIT && return_value != EXIT_SUCCESS)
	{
		free(cub3d);
		return(return_value);
	}
	free_parsing_content(parsing);
	free(parsing);
	free(cub3d);
	return (return_value);

	printf("fail malloc parsing\n");
	free(cub3d);
	return(2); //TODEFINE
}
