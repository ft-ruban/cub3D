/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_rgb_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:26:56 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 10:23:57 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1) here we fill the ptr to the variable that is supposed to hold the value
//    it would be convert from char* into an int and check all the cases
//    that could lead to error or invalid format. (like it doesnt overflow the
//    0-255 value expected, that it is a number that we dont get more than 3 num
//    that a ',' is truly between each color value...

static bool	retrieve_rgb(int fd_sd, t_cub3d *cub3d, int *ptr_data_to_fill,
		bool is_blue)
{
	size_t	len_rgb_value;

	len_rgb_value = 1;
	*ptr_data_to_fill = ft_atoi(&cub3d->parsing->buff[0]);
	if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
		return (error_handler(cub3d, INV_CON_RGB, FILE_ERR_8, MSG_6));
	if (is_blue && cub3d->parsing->buff[0] == '\n')
		return (RETURN_SUCCESS);
	while (cub3d->parsing->buff[0] != ',' || is_blue)
	{
		if (ft_isnum((int)cub3d->parsing->buff[0]) || len_rgb_value > 3)
			return (error_handler(cub3d, INV_CON_RGB,
					"element_rgb_parsing.c:34 ", MSG_8));
		*ptr_data_to_fill = *ptr_data_to_fill * 10;
		*ptr_data_to_fill = *ptr_data_to_fill
			+ ft_atoi(&cub3d->parsing->buff[0]);
		if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
			return (error_handler(cub3d, INV_CON_RGB, FILE_ERR_6, MSG_6));
		len_rgb_value++;
		if (is_blue && cub3d->parsing->buff[0] == '\n')
			break ;
	}
	if (*ptr_data_to_fill < 0 || *ptr_data_to_fill > 255 || len_rgb_value > 3)
		return (error_handler(cub3d, INV_CON_RGB, FILE_ERR_9, MSG_8));
	return (RETURN_SUCCESS);
}

// 1) we just call retrieve rgb here, but with an extra verification at the end
//    if we are not dealing with a blue value (last one) then we read further
//    and expect a num here if we dont catch one it mean the file is probably
//    invalid so we return an error and stop the collect.

static bool	prepare_retrieve_rgb(int fd_sd, t_cub3d *cub3d, bool is_blue,
		int *ptr_data_to_fill)
{
	if (retrieve_rgb(fd_sd, cub3d, ptr_data_to_fill, is_blue))
		return (RETURN_FAILURE);
	if (!is_blue)
	{
		if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
			return (error_handler(cub3d, INV_CON_RGB,
					"element_rgb_parsing.c:63 ", MSG_6));
		if (ft_isnum((int)cub3d->parsing->buff[0]))
			return (error_handler(cub3d, INV_CON_RGB,
					"element_rgb_parsing.c:66 ", MSG_8));
	}
	return (RETURN_SUCCESS);
}
// 1) that function will just call 3 time for the three part of the data
//    (red, greem, blue) and depending of the parameter sent it will know
//		which data we are dealing with (if it is ceil or floor).

static bool	ceil_or_floor_rgb(int fd_sd, t_cub3d *cub3d, bool ceil_or_floor)
{
	if (ceil_or_floor == CEIL)
	{
		if (prepare_retrieve_rgb(fd_sd, cub3d, false, &cub3d->parsing->ceil_r))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, cub3d, false, &cub3d->parsing->ceil_g))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, cub3d, true, &cub3d->parsing->ceil_b))
			return (RETURN_FAILURE);
	}
	else if (ceil_or_floor == FLOOR)
	{
		if (prepare_retrieve_rgb(fd_sd, cub3d, false, &cub3d->parsing->floor_r))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, cub3d, false, &cub3d->parsing->floor_g))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, cub3d, true, &cub3d->parsing->floor_b))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// 1) we know we are dealing with an rgb value, we ignore all spaces that could
//    be between the declaration and the value.
// 2) depending of what rgb value we are dealing with we go to ceil_or_floor
//    with different parameters to fill the matching data.
//    if for some reasons we stop having spaces before getting into a number
//    we return an error.

bool	is_rgb_valid(int fd_sd, t_cub3d *cub3d, char first_letter,
		bool received_rgb_completed)
{
	while (!received_rgb_completed)
	{
		if (cub3d->parsing->buff[0] == ' ')
		{
			if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
				return (error_handler(cub3d, INV_CON_RGB, FILE_ERR_10, MSG_6));
		}
		if (!ft_isnum((int)cub3d->parsing->buff[0]) && cub3d->parsing->buff[0])
		{
			if (first_letter == 'F')
			{
				if (ceil_or_floor_rgb(fd_sd, cub3d, FLOOR))
					return (RETURN_FAILURE);
			}
			else
			{
				if (ceil_or_floor_rgb(fd_sd, cub3d, CEIL))
					return (RETURN_FAILURE);
			}
			received_rgb_completed = true;
		}
		else if (cub3d->parsing->buff[0] != ' ')
			return (error_handler(cub3d, INV_CON_RGB, FILE_ERR_7, MSG_7));
	}
	return (RETURN_SUCCESS);
}
