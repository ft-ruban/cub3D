#include "set_mlx.h"
#include "parsing.h"
#include <unistd.h> //write
# include "../minilibx-linux/mlx.h"

// static int mlx_prepare_initialization(t_mlx *screen)
// {
// 	if(init_param() == 1)
// 		return(RETURN_FAILURE); //TOPROTECT BETTER
// 	if (init_screen_mlx(screen) == NULL)
// 		return(RETURN_FAILURE);	
// 	return (RETURN_SUCCESS);
// }

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
	//WIP MLX
	screen = calloc(1, sizeof(t_mlx)); //TOPROTECT
	init_screen_mlx(screen); //TOPROTECT
	mlx_hook(screen->mlx_win, 17, 1L << 17, close_window, screen);
	mlx_hook(screen->mlx_win, 2, 1L << 0, handle_keys, screen);
	// mlx_mouse_hook(screen->mlx_win, zoom, &param);
	//mlx_loop_hook(screen->mlx, set, &screen);
	mlx_loop_hook(screen->mlx, draw, screen);
	mlx_loop(screen->mlx);
	print_struct_set(set); // DEBUG function to see content of struct set

	return (clean_and_exit(set));
}
