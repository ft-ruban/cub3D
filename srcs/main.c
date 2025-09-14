/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:06:20 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/14 14:30:34 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h> //write
# include "../minilibx-linux/mlx.h"

// We init them at those value for further processing in the parsing
static void	init_struct_value(t_settings *set)
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

static void	free_all(t_settings *set)
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

static int	clean_and_exit(t_settings *set)
{
	unsigned char	return_value;

	return_value = set->error_type;
	printf("\n\nRETURN CODE : %u\n", return_value); //TORM THIS IS DEBBUG LINE
	free_all(set);
	free(set);
	return (return_value);
}

// TODO FREE CONTENT STRUCT?

int	main(int argc, char *argv[])
{
	t_mlx		*screen;
	t_settings	*set;

	screen = NULL;
	set = malloc(sizeof(t_settings));
	if (!set)
		return (error_handler(NULL, MAL_ERR_SET, "main:TOFILL ", MSG_1));
	init_struct_value(set);
	if (parsing(argc, argv, set))
		return (clean_and_exit(set));
	print_struct_set(set); // DEBUG function to see content of struct set
	//-------------------------------------------------------
	//--------------PSEUDOCODE-------------------------------
	//-------------------------------------------------------
	// init structures/data
	// if fail return error with right msg + free close
	// init minilibx + I guess the controls?
	// if fail return error with right msg + free/close
	// running part
	//-------------------------------------------------------
	//--------------PSEUDOCODE-------------------------------
	//-------------------------------------------------------
	return (clean_and_exit(set));
}
