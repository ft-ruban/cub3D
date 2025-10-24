#include "../minilibx-linux/mlx.h"
#include "exec.h"
#include "parsing.h"
#include "set_mlx.h"
#include <unistd.h> //write

static bool free_all_err(t_img *no, t_img *ea, t_img *so, t_img *we)
{
	if(no)
		free(no);	
	if(ea)
		free(ea);
	if(so)
		free(so);
	if(we)
		free(we);
	return(1);
}

static bool malloc_cardinal_point_struct(t_texture *texture)
{
	t_img 		*no;
	t_img  		*so;
	t_img  		*we;
	t_img  		*ea;

	no = NULL; //superflu?
	so = NULL;
	we = NULL;
	ea = NULL;
	no = NULL;//malloc(sizeof(t_img));
	so = malloc(sizeof(t_img));
	we = malloc(sizeof(t_img));
	ea = malloc(sizeof(t_img));
	if (!no || !so || !we || !ea)
		return(free_all_err(no, ea, so, we));
	texture->no = no;
	texture->so = so;
	texture->we = we;
	texture->ea = ea;
	return(RETURN_SUCCESS);
}

static bool init_img_texture(t_img *texture, t_mlx *mlx, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx, path,0,0); //TOASKMATHISU x2)
	if(!texture->img)
		return(RETURN_FAILURE);
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bits_per_pixel),
	 &(texture->line_length), &(texture->endian));
	texture->bits_per_pixel = texture->bits_per_pixel >> 3; //TO ASK ABOUT THE VALUE;
	return(RETURN_SUCCESS);
}

static bool init_textures_img(t_cub3d *cub3d)
{
	if(malloc_cardinal_point_struct(cub3d->texture))
		return(RETURN_FAILURE); //toprotect
	if(init_img_texture(cub3d->texture->no, cub3d->mlx, cub3d->parsing->rp_no))
		printf("FAIL\n");//TOPROTECT
	if(init_img_texture(cub3d->texture->so, cub3d->mlx, cub3d->parsing->rp_so))
		printf("FAIL\n"); //TOPROTECT	//TODO init t_img des textures SO
	if(init_img_texture(cub3d->texture->we, cub3d->mlx, cub3d->parsing->rp_we))
		printf("FAIL\n"); //TOPROTECT	//TODO init t_img des textures EA
	if(init_img_texture(cub3d->texture->ea, cub3d->mlx, cub3d->parsing->rp_ea))
		printf("FAIL\n"); //TOPROTECT
	return(RETURN_SUCCESS);
}
static bool init_ray(t_cub3d *cub3d)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	if(!ray)
	{
		return (RETURN_FAILURE); //TOPROTECT
	}
	cub3d->ray = ray;
	//IF NEEDED we can assign default value HERE
	return(RETURN_SUCCESS);
}

static int init_mlx_texture_img(t_cub3d *cub3d)
{
	t_mlx *mlx;

	mlx = NULL;
	mlx = init_screen_mlx(mlx);
	if (!mlx)
	{
		error_handler(cub3d, INIT_LIBX_FAILED, "main:TOFILL ", MSG_ERR_MLX);
		free_map(cub3d->map);
		free(cub3d->texture);
		return (clean_and_exit(cub3d, cub3d->parsing, NULL));
	}
	cub3d->mlx = mlx;
	if(init_textures_img(cub3d))
		return(RETURN_FAILURE); //TOPROTECT?
	init_ray(cub3d); //TOPROTECT
	return(RETURN_SUCCESS);
}

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
	if (parsing_init(argc, argv, cub3d))
		return (clean_and_exit(cub3d));
	if (init_mlx_texture_img(cub3d)) //TOPROTECT
		return (clean_and_exit(cub3d));
	hook_and_loop(cub3d, cub3d->mlx);
	destroy_free_screen(cub3d->mlx);
	print_struct_parsing(cub3d->parsing); // TODLDEBUG function to see content of struct set
	free_map(cub3d->map);
	free(cub3d->map);
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
