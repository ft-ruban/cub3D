/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:26:56 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/12 14:26:57 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>    //open
#include <stdbool.h>  //bool duh
#include <stdio.h>    //printf
#include <sys/stat.h> //open

static int	retrieve_rgb(int fd_sd, t_settings *set, int *ptr_data_to_fill,
		bool is_blue)
{
	size_t	len_rgb_value;

	len_rgb_value = 0;
	*ptr_data_to_fill = ft_atoi(&set->buff[0]);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c: ", MSG_6));
	while (set->buff[0] != ',')
	{
		if (ft_isnum((int)set->buff[0]) || len_rgb_value > 3)
			return (error_handler(set, PAR_INV_RGB, "parsing_rgb.c: ", MSG_8));
		*ptr_data_to_fill = *ptr_data_to_fill * 10;
		*ptr_data_to_fill = *ptr_data_to_fill + ft_atoi(&set->buff[0]);
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_rgb.c: ", MSG_6));
		len_rgb_value++;
		if (is_blue && set->buff[0] == '\n')
			break ;
	}
	if (*ptr_data_to_fill < 0 || *ptr_data_to_fill > 255)
		return (error_handler(set, PAR_INV_RGB, "parsing_rgb.c: ", MSG_8));
	return (RETURN_SUCCESS);
}

static int	retrieve_rgb_calling(int fd_sd, t_settings *set, bool floor_or_cell)
{
	if (floor_or_cell == FLOOR)
	{
		if (retrieve_rgb(fd_sd, set, &set->floor_r, false))
			return (RETURN_FAILURE);
		if (retrieve_rgb(fd_sd, set, &set->floor_g, false))
			return (RETURN_FAILURE);
		if (retrieve_rgb(fd_sd, set, &set->floor_b, true))
			return (RETURN_FAILURE);
	}
	else if (floor_or_cell == CELL)
	{
		if (retrieve_rgb(fd_sd, set, &set->cell_r, false))
			return (RETURN_FAILURE);
		if (retrieve_rgb(fd_sd, set, &set->cell_g, false))
			return (RETURN_FAILURE);
		if (retrieve_rgb(fd_sd, set, &set->cell_b, true))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// this is not the releasable name!!!
int	rgb_thing(int fd_sd, t_settings *set, char first_letter, bool exit_loop)
{
	while (!exit_loop)
	{
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_rgb.c: ", MSG_6));
		if (ft_isnum((int)set->buff[0]) == RETURN_SUCCESS)
		{
			if (first_letter == 'F')
			{
				if (retrieve_rgb_calling(fd_sd, set, FLOOR))
					return (RETURN_FAILURE);
			}
			else
			{
				if (retrieve_rgb_calling(fd_sd, set, CELL))
					return (RETURN_FAILURE);
			}
			exit_loop = true;
		}
		else if (set->buff[0] != ' ')
			return (error_handler(set, INV_CON, "parsing_rgb.c", MSG_7));
	}
	return (RETURN_SUCCESS);
}
