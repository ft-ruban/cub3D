/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_rgb_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:26:56 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/25 08:50:04 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// we get the first number, then we get into a loop that would continue
// until we reach the ',' char or until an error is met. if the next char
// is not a num error OR is bigger than 3digits ERROR
// else we multiply by 10 and get the next number
// into the ptr to our variable to get the right value in the end
// if the value is not a num between 0 and 255 then it mean it is an invalid
// rgb value

static bool	retrieve_rgb(int fd_sd, t_settings *set, int *ptr_data_to_fill,
		bool is_blue)
{
	size_t	len_rgb_value;

	len_rgb_value = 1;
	*ptr_data_to_fill = ft_atoi(&set->buff[0]);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (is_blue && set->buff[0] == '\n')
		return (RETURN_SUCCESS);
	while (set->buff[0] != ',' || is_blue)
	{
		if (ft_isnum((int)set->buff[0]) || len_rgb_value > 3)
			return (error_handler(set, PAR_INV_RGB, "parsing_rgb.c:34 ",
					MSG_8));
		*ptr_data_to_fill = *ptr_data_to_fill * 10;
		*ptr_data_to_fill = *ptr_data_to_fill + ft_atoi(&set->buff[0]);
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_rgb.c:39 ", MSG_6));
		len_rgb_value++;
		if (is_blue && set->buff[0] == '\n')
			break ;
	}
	if (*ptr_data_to_fill < 0 || *ptr_data_to_fill > 255 || len_rgb_value > 3)
		return (error_handler(set, PAR_INV_RGB, "parsing_rgb.c:45 ", MSG_8));
	return (RETURN_SUCCESS);
}

// we call retrieve_rgb 3 time to fill the red part, green and blue one

static bool	prepare_retrieve_rgb_ceil(int fd_sd, t_settings *set)
{
	if (retrieve_rgb(fd_sd, set, &set->ceil_r, false))
		return (RETURN_FAILURE);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (retrieve_rgb(fd_sd, set, &set->ceil_g, false))
		return (RETURN_FAILURE);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (retrieve_rgb(fd_sd, set, &set->ceil_b, true))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static bool	prepare_retrieve_rgb_floor(int fd_sd, t_settings *set)
{
	if (retrieve_rgb(fd_sd, set, &set->floor_r, false))
		return (RETURN_FAILURE);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (retrieve_rgb(fd_sd, set, &set->floor_g, false))
		return (RETURN_FAILURE);
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (retrieve_rgb(fd_sd, set, &set->floor_b, true))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// while we didnt retrieve our rgb value we stay in loop
// we read char by char the content, if it is a num value
// we redirect to the next function with the right parameter
// depending if it is about floor or ceiling and put our bool at true
// to exit the loop. If it is a space char we get back to the start of loop
// else it mean it is an invalid content so in consequence return an error

//TODO  TO CHECK IF NECC? c:103

bool	is_rgb_valid(int fd_sd, t_settings *set, char first_letter,
		bool received_rgb_completed)
{
	while (!received_rgb_completed)
	{
		if (set->buff[0] == ' ')
		{
			if (read(fd_sd, set->buff, 1) == -1)
				return (error_handler(set, INV_READ, FILE_ERR_1, MSG_6));
		}
		if (!ft_isnum((int)set->buff[0]) && set->buff[0])
		{
			if (first_letter == 'F')
			{
				if (prepare_retrieve_rgb_floor(fd_sd, set))
					return (RETURN_FAILURE);
			}
			else
			{
				if (prepare_retrieve_rgb_ceil(fd_sd, set))
					return (RETURN_FAILURE);
			}
			received_rgb_completed = true;
		}
		else if (set->buff[0] != ' ')
			return (error_handler(set, INV_CON, "parsing_rgb.c:106 ", MSG_7));
	}
	return (RETURN_SUCCESS);
}
