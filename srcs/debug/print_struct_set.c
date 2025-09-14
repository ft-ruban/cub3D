/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:59:44 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/14 12:41:28 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "debug.h"
#include "parsing.h"

void	print_struct_set(t_settings *set)
{
	printf("\n\nDEBUG\nrp_no = %s\n", set->rp_no);
	printf("rp_so = %s\n", set->rp_so);
	printf("rp_we = %s\n", set->rp_we);
	printf("rp_ea = %s\n", set->rp_ea);
	printf("floor_r = %d\n", set->floor_r);
	printf("floor_g = %d\n", set->floor_g);
	printf("floor_b = %d\n", set->floor_b);
	printf("cell_r = %d\n", set->ceil_r);
	printf("cell_g = %d\n", set->ceil_g);
	printf("cell_b = %d\n", set->ceil_b);
}
