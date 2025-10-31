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

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (error_handler(NULL, CUB_SET_FAIL, "main:TOFILL ", MSG_1));
	cub3d->error_type = ALL_OK;
	cub3d->print = true;
	if (parsing_init(argc, argv, cub3d))
		return (clean_and_exit(cub3d));
	if (init_mlx_texture_img(cub3d))
		return (clean_and_exit(cub3d));
	hook_and_loop(cub3d, cub3d->mlx);
	//print_struct_parsing(cub3d->parsing); // TODLDEBUG function to see content of struct set
	// free_map(cub3d->map);
	// free(cub3d->map);
	//free(cub3d->texture);
	return (clean_and_exit(cub3d));
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
