#include "set_mlx.h"

// LDEV: can be completed with more key code for further commands
// 65361 = left arrow
// 65362 = up arrow
// 65363 = right arrow
// 65364 = bottom arrow
// use the printf of the keycode to find new keycode AND DEFINE for better
// readability
// USE FORMAT: KEY_LEFTARR | KEY_X

// stop the loop to make our loop stop to close the windows properly and exit
// the program

int	close_window(t_mlx *screen)
{
	mlx_loop_end(screen->ptr);
	return (RETURN_SUCCESS);
}

// handle keys entered during the exec or program
// keycode == the key used before entering into function
// LDEV: Use the printf to know which keycode we need for a specific key
// 			and define it for readability + better futur maintenance.

int	handle_keys(int keycode, t_mlx *screen)
{
	printf("key : %d\n", keycode); // TODL USED TO FIND KEY CODES
	if (keycode == KEY_ESC)
		return (close_window(screen));
	return (KEY_UNKNOWN);
}

// ex of use for ex
// if (keycode == 65361 || keycode == 65362 || keycode == 65363
// 	|| keycode == 65364)
// 	return (key_move(keycode & 0x7, param));
// else
// {
// 	if (change_color(&param->color_factor) == 1)
// 		return (close_window(param));
// }