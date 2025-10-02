#include "../minilibx-linux/mlx.h"
#include "exec.h"
#include "parsing.h"
#include "set_mlx.h"
#include <unistd.h> //write

// WIP DOC : we init our setting structure, then its value then we parse the
// arguments + content of the file in (parsing) before handling the initiation
// of MLX that would lead to the loop/hook that handle event and interaction
// with our project

// TODO util main function to clean up things depending of the error case!
// TODO when work is finished to describe the main in commentaries
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
	// WIP MLX
	screen = init_screen_mlx(screen); // TOPROTECT
	if (!screen)
	{
		error_handler(set, INIT_LIBX_FAILED, "main:TOFILL ", MSG_ERR_MLX);
		free_map(set);
		return (clean_and_exit(set));
	}
	hook_and_loop(screen);
	destroy_free_screen(screen);
	print_struct_set(set); // TODLDEBUG function to see content of struct set
	free_map(set);
	return (clean_and_exit(set));
}
//-----------------------------------------------------------------------------
// to free everything before leaving
// CECI EST UNE FONCTION QUE J'AI FAIS DANS UN AUTRE PROJET QUI POURRAIT SERVIR
// PLUS TARD POUR GAGNER DU TEMPS

// int	free_all_mlx(t_mlx *screen, t_set_call *param, int error_code)
// {
// 	if (screen)
// 		free(screen);
// 	if (param->c)
// 		free(param->c);
// 	if (param->z)
// 		free(param->z);
// 	if (error_code == 6)
// 		return (RETURN_FAILURE);
// 	if (error_code == -1)
// 		return (1);
// 	else
// 		return (RETURN_FAILURE);
// }
//-----------------------------------------------------------------------------
