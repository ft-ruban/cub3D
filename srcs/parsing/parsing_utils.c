/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:53:11 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 11:53:36 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// initiation of parsing struct and we set everything at NULL or -1 by default

bool	init_parsing_struct(t_cub3d *cub3d)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (RETURN_FAILURE);
	cub3d->parsing = parsing;
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
	return (RETURN_SUCCESS);
}

// Here we check if the file sent do possess the right
//.cub extension by checking the last characters in the
// given string of char

bool	is_file_cub_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 3] != '.' || file[len - 2] != 'c' || file[len - 1] != 'u'
		|| file[len] != 'b')
		return (false);
	return (true);
}
