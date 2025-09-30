/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/23 12:32:55 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

// We init them at those value for further processing in the parsing
void	init_struct_value(t_settings *set)
{
	set->buff = NULL;
	set->rp_no = NULL;
	set->rp_so = NULL;
	set->rp_we = NULL;
	set->rp_ea = NULL;
	set->ceil_r = NONE_ASSIGNED;
	set->ceil_g = NONE_ASSIGNED;
	set->ceil_b = NONE_ASSIGNED;
	set->floor_r = NONE_ASSIGNED;
	set->floor_g = NONE_ASSIGNED;
	set->floor_b = NONE_ASSIGNED;
	set->error_type = RETURN_SUCCESS;
}

void	free_all(t_settings *set)
{
	if (set->buff)
		free(set->buff);
	if (set->rp_no)
		free(set->rp_no);
	if (set->rp_so)
		free(set->rp_so);
	if (set->rp_we)
		free(set->rp_we);
	if (set->rp_ea)
		free(set->rp_ea);
	get_next_line(-1);
}

int	clean_and_exit(t_settings *set)
{
	unsigned char	return_value;

	return_value = set->error_type;
	printf("\n\nRETURN CODE : %u\n", return_value); //TORM THIS IS DEBBUG LINE
	free_all(set);
	free(set);
	return (return_value);
}