/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:59:25 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 13:59:28 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// here
// TOTEST (should be good enough but you never know?)

bool	free_map_cpmap_failed(size_t line_index, t_map *map_info)
{
	while (line_index != 0)
	{
		free(map_info->map[line_index - 1]);
		line_index--;
	}
	return (-1);
}

void	free_map(t_map *map_info)
{
	int	i;

	i = 0;
	while (map_info->map[i])
	{
		free(map_info->map[i]);
		i++;
	}
	free(map_info->map);
	free(map_info);
}
