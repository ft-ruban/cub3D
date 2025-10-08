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
	t_cub3d		*cub3d;
	//t_mlx		*mlx;
	//t_parsing	*parsing;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (error_handler(NULL, MAL_ERR_SET, "main:TOFILL ", MSG_1));
	if (parsing_init(argc, argv, cub3d))
		return (clean_and_exit(NULL));
	// WIP MLX
	// t_mlx = init_screen_mlx(t_mlx); // TOPROTECT
	// if (!t_mlx)
	// {
	// 	error_handler(set, INIT_LIBX_FAILED, "main:TOFILL ", MSG_ERR_MLX);
	// 	free_map(set);
	// 	return (clean_and_exit(set));
	// }
	// hook_and_loop(t_mlx);
	// destroy_free_screen(t_mlx);
	// print_struct_set(set); // TODLDEBUG function to see content of struct set
	// free_map(set);
	// return (clean_and_exit(set));
	return(0);
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
