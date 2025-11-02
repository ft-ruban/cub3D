/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:02:25 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 09:15:42 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// that util function is used to write an error msg
// that is sent in param and to setup error_type
// with the right error code

void	*error_handler_void(t_cub3d *cub3d, int error_type,
			char *emplacement_error_msg, char *err_msg)
{
	write(2, emplacement_error_msg, ft_strlen(emplacement_error_msg));
	write(2, err_msg, ft_strlen(err_msg));
	cub3d->error_type = error_type;
	return (NULL);
}

int	error_handler(t_cub3d *cub3d, int error_type, char *emplacement_error_msg,
		char *err_msg)
{
	size_t emp_err_msg_len;
	size_t err_msg_len;

	emp_err_msg_len = ft_strlen(emplacement_error_msg);
	err_msg_len = ft_strlen(err_msg);
	write(2, emplacement_error_msg, emp_err_msg_len);
	write(2, err_msg, err_msg_len);
	if (error_type == CUB_SET_FAIL)
		return (CUB_SET_FAIL);
	cub3d->error_type = error_type;
	return (RETURN_FAILURE);
}
