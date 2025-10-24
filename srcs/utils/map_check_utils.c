#include "utils.h"

bool	character_is_invalid(char c)
{
	if (c != '1' && c != '0' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W'
		&& c != '\0' && c != '\n' && c != ' ')
		return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

bool	player_update_check(t_cub3d *cub3d, bool *player)
{
	if (*player == true)
		return(RETURN_FAILURE);
	else //more than one player
		*player = true;
	return (RETURN_SUCCESS);
}
