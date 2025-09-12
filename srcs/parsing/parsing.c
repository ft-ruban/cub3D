/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/12 16:13:58 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h> //for printf TORM

// Here we check if the file sent do possess the right
//.cub extension

static bool	is_right_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// TODO next step would be to parse the map.
// Or is that for later? need to talk about it
// to know the course of action,
// in any case need to close fd at some point! also if we need
// to use the fd later on then would be better to save it in our set struct.
// TORM LIGNE 31 + 32
int	parsing(int argc, char *argv[], t_settings *set)
{
	int	fd;

	if (argc != 2)
		return (error_handler(set, PAR_NBR_ARGC, "parsing.c:25 ", MSG_2));
	if (is_right_extension(argv[1]))
		return (error_handler(set, PAR_EXTENSION, "parsing.c:27 ", MSG_3));
	if (open_file_collect_elements(argv[1], set, &fd))
		return (RETURN_FAILURE);
	if (get_and_check_map(argv[1], set, fd))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
