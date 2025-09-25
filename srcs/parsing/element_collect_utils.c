/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_collect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:49:00 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/25 08:49:20 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// here we open a given file by checking in
// the map folder.
// it return the fd that hold the return of our open.
// if no readable file with the right name found fd would be = to -1
// that should be checked by the calling function.

int	open_sd_file_give_fd(char *file)
{
	char	*path;
	int		fd_sd;

	path = ft_strjoin(MAP_FOLDER_PATH, file);
	if (!path)
		return (OPEN_FAILED);
	fd_sd = open(path, O_RDONLY);
	free(path);
	return (fd_sd);
}

int	which_element_type(char letter, t_settings *set)
{
	if ((letter == 'F' && set->floor_r == NONE_ASSIGNED) || (letter == 'C'
			&& set->ceil_r == NONE_ASSIGNED))
		return (TYPE_RGB);
	else if (letter == 'N' || letter == 'S' || letter == 'W' || letter == 'E')
		return (TYPE_TEXTURE);
	else if (letter == '\n')
		return (TYPE_EMPTY_LINE);
	else
		return (INVALID);
}

// that function's goal is to check if there is a missing element's
// content in our set struct
// if nothing is missed then return false to make the loop stop
// else it send a true to make it continue

bool	an_element_is_missing(t_settings *set)
{
	if (!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea
		|| set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED
		|| set->floor_b == NONE_ASSIGNED || set->ceil_r == NONE_ASSIGNED
		|| set->ceil_g == NONE_ASSIGNED || set->ceil_b == NONE_ASSIGNED)
		return (true);
	else
		return (false);
}
