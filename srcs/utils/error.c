/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:02:25 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 16:28:01 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// 1) receive as arg an int that will hold the errortype to transfer to our main
//   struct, also the main struct (here cub3d) as the two error msg that is
//   wanted to print thanks to write().
// 2) we strlen the msg sent that would be used in our write of 2 (errorfd)
//   to print the exact error msg we desire.
// 3) then we give to cub3d the value of the error type that would be used to
//   free properly in the right order and also to return the right error value
//   for easier debbuging as the code was imagined as a project that can be
//   maintained as easier as possible.

int	error_handler(t_cub3d *cub3d, int error_type, char *emplacement_error_msg,
		char *err_msg)
{
	size_t	emp_err_msg_len;
	size_t	err_msg_len;

	write(2,"Error\n",6);
	emp_err_msg_len = ft_strlen(emplacement_error_msg);
	err_msg_len = ft_strlen(err_msg);
	write(2, emplacement_error_msg, emp_err_msg_len);
	write(2, err_msg, err_msg_len);
	if (error_type == CUB_SET_FAIL)
		return (CUB_SET_FAIL);
	cub3d->error_type = error_type;
	return (RETURN_FAILURE);
}
