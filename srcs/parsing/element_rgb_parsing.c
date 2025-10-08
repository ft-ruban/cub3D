/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_rgb_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:26:56 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/08 16:13:55 by ldevoude         ###   ########.fr       */
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

static bool	retrieve_rgb(int fd_sd, t_parsing *parsing, int *ptr_data_to_fill,
		bool is_blue)
{
	size_t	len_rgb_value;

	len_rgb_value = 1;
	*ptr_data_to_fill = ft_atoi(&parsing->buff[0]);
	if (read(fd_sd, parsing->buff, 1) == -1)
		return (error_handler(parsing, INV_READ, "parsing_rgb.c:30 ", MSG_6));
	if (is_blue && parsing->buff[0] == '\n')
		return (RETURN_SUCCESS);
	while (parsing->buff[0] != ',' || is_blue)
	{
		if (ft_isnum((int)parsing->buff[0]) || len_rgb_value > 3)
			return (error_handler(parsing, PAR_INV_RGB, "parsing_rgb.c:34 ",
					MSG_8));
		*ptr_data_to_fill = *ptr_data_to_fill * 10;
		*ptr_data_to_fill = *ptr_data_to_fill + ft_atoi(&parsing->buff[0]);
		if (read(fd_sd, parsing->buff, 1) == -1)
			return (error_handler(parsing, INV_READ, "parsing_rgb.c:39 ", MSG_6));
		len_rgb_value++;
		if (is_blue && parsing->buff[0] == '\n')
			break ;
	}
	if (*ptr_data_to_fill < 0 || *ptr_data_to_fill > 255 || len_rgb_value > 3)
		return (error_handler(parsing, PAR_INV_RGB, "parsing_rgb.c:45 ", MSG_8));
	return (RETURN_SUCCESS);
}

static bool	prepare_retrieve_rgb(int fd_sd, t_parsing *parsing, bool is_blue,
		int *ptr_data_to_fill)
{
	if (retrieve_rgb(fd_sd, parsing, ptr_data_to_fill, is_blue))
		return (RETURN_FAILURE);
	if (!is_blue)
	{
		if (read(fd_sd, parsing->buff, 1) == -1)
			return (error_handler(parsing, INV_READ, "parsing_rgb.c:30 ", MSG_6));
		if (ft_isnum((int)parsing->buff[0]))
			return (error_handler(parsing, PAR_INV_RGB, "parsing_rgb.c:60 ",
					MSG_8));
	}
	return (RETURN_SUCCESS);
}

// we call retrieve_rgb 3 time to fill the red part, green and blue one

static bool	ceil_or_floor_rgb(int fd_sd, t_parsing *parsing, bool ceil_or_floor)
{
	if (ceil_or_floor == CEIL)
	{
		if (prepare_retrieve_rgb(fd_sd, parsing, false, &parsing->ceil_r))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, parsing, false, &parsing->ceil_g))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, parsing, true, &parsing->ceil_b))
			return (RETURN_FAILURE);
	}
	else if (ceil_or_floor == FLOOR)
	{
		if (prepare_retrieve_rgb(fd_sd, parsing, false, &parsing->floor_r))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, parsing, false, &parsing->floor_g))
			return (RETURN_FAILURE);
		if (prepare_retrieve_rgb(fd_sd, parsing, true, &parsing->floor_b))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// static bool	prepare_retrieve_rgb_floor(int fd_sd, t_settings *set)
// {
// 	if (retrieve_rgb(fd_sd, set, &set->floor_r, false))
// 		return (RETURN_FAILURE);
// 	if (read(fd_sd, set->buff, 1) == -1)
// 		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
// 	if (retrieve_rgb(fd_sd, set, &set->floor_g, false))
// 		return (RETURN_FAILURE);
// 	if (read(fd_sd, set->buff, 1) == -1)
// 		return (error_handler(set, INV_READ, "parsing_rgb.c:30 ", MSG_6));
// 	if (retrieve_rgb(fd_sd, set, &set->floor_b, true))
// 		return (RETURN_FAILURE);
// 	return (RETURN_SUCCESS);
// }

// while we didnt retrieve our rgb value we stay in loop
// we read char by char the content, if it is a num value
// we redirect to the next function with the right parameter
// depending if it is about floor or ceiling and put our bool at true
// to exit the loop. If it is a space char we get back to the start of loop
// else it mean it is an invalid content so in consequence return an error

// TODO  TO CHECK IF NECC? c:103

bool	is_rgb_valid(int fd_sd, t_parsing *parsing, char first_letter,
		bool received_rgb_completed)
{
	while (!received_rgb_completed)
	{
		if (parsing->buff[0] == ' ')
		{
			if (read(fd_sd, parsing->buff, 1) == -1)
				return (error_handler(parsing, INV_READ, FILE_ERR_1, MSG_6));
		}
		if (!ft_isnum((int)parsing->buff[0]) && parsing->buff[0])
		{
			if (first_letter == 'F')
			{
				if (ceil_or_floor_rgb(fd_sd, parsing, FLOOR))
					return (RETURN_FAILURE);
			}
			else
			{
				if (ceil_or_floor_rgb(fd_sd, parsing, CEIL))
					return (RETURN_FAILURE);
			}
			received_rgb_completed = true;
		}
		else if (parsing->buff[0] != ' ')
			return (error_handler(parsing, INV_CON, "parsing_rgb.c:106 ", MSG_7));
	}
	return (RETURN_SUCCESS);
}
