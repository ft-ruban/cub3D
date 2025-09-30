/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:01:46 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/14 12:01:58 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (RETURN_SUCCESS);
	else
		return (RETURN_FAILURE);
}
