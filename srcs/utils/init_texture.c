#include "cub3D.h"

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
	no = malloc(sizeof(t_img));
	so = malloc(sizeof(t_img));
	we = malloc(sizeof(t_img));
	ea = malloc(sizeof(t_img));
	if (!no || !so || !we || !ea)
		return(free_all(no, ea, so, we));
	texture->no = no;
	texture->so = so;
	texture->we = we;
	texture->ea = ea;
	return(RETURN_SUCCESS);
}

bool	init_texture_struct(t_cub3d *cub3d, t_texture *texture)
{
	if(malloc_cardinal_point_struct(texture))
	{
		free(texture); //???
		return(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
