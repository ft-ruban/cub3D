/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:02:25 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/11 11:17:28 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// that util function is used to write an error msg
// that is sent in param and to setup error_type
// with the right error code

int	error_handler(t_parsing *parsing, int error_type, char *emplacement_error_msg,
		char *err_msg)
{
	write(2, emplacement_error_msg, ft_strlen(emplacement_error_msg));
	write(2, err_msg, ft_strlen(err_msg));
	if (error_type == MAL_ERR_SET)
		return (MAL_ERR_SET);
	parsing->error_type = error_type;
	return (RETURN_FAILURE);
}
