/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:02:25 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/14 12:04:25 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// that util function is used to write an error msg
// that is sent in param and to setup error_type
// with the right error code

int	error_handler(t_settings *set, int error_type, char *emplacement_error_msg,
		char *err_msg)
{
	write(2, emplacement_error_msg, ft_strlen(emplacement_error_msg));
	write(2, err_msg, ft_strlen(err_msg));
	if (error_type == MAL_ERR_SET)
		return (MAL_ERR_SET);
	set->error_type = error_type;
	return (RETURN_FAILURE);
}
