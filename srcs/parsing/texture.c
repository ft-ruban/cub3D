/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:53:03 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 10:50:54 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1) we convert our rgb into a single usable value that can be read as an hex
//    value 
// 2) & 0xff is a AND binary operation to mask the value to only keep the
//    lowest 8 bits of each int values between 0 and 255 (in our project
//    it is not that important considering we do not allow values above 255 
//    before that operation was made we did it to make that function usable
//    elsewhere for a new project or for someone else.
// 3) << 16 is used so the red goes at the highest byte position (16-23)
// 4) << 8 to make it at the middle position for the green value (8-15)
// 5) blue is not shifted it stays in the lowest byte (0-7)
// 6) congratz

static void	convert_rgb_hex(t_parsing *parsing, t_texture *texture)
{
	texture->ceil_hex = ((parsing->ceil_r & 0xff) << 16)
		+ ((parsing->ceil_g & 0xff) << 8) + (parsing->ceil_b & 0xff);
	texture->floor_hex = ((parsing->floor_r & 0xff) << 16)
		+ ((parsing->floor_g & 0xff) << 8) + (parsing->floor_b & 0xff);
}

// 1) here we set our texture struct
// 2) convert the rgb value we caught in the file into a hexadecimal value

bool	texture_struct_setup(t_cub3d *cub3d)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	cub3d->texture = texture;
	if (!texture)
		return (RETURN_FAILURE);
	convert_rgb_hex(cub3d->parsing, texture);
	return (RETURN_SUCCESS);
}
