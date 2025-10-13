#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// 
void	find_tex_x(t_data *data)
{
	
}

// if side = 0, the wall enconter is on the x axe, so it is either the east or
// west texture.
// if side = 1, on the y axe, the texture will be the north or south one.
char	*right_texture_addr(t_data *data)
{
	char	*ptr_texture;

	if (data->side == 0)
	{
		if (data->ray_dir_x < 0)
			ptr_texture = data->texture->we_addr;
		else
			ptr_texture = data->texture->ea_addr;
	}
	else
	{
		if (data->ray_dir_y < 0)
			ptr_texture = data->texture->so_addr;
		else
			ptr_texture = data->texture->no_addr;
	}
}

// the texture is contain in a linear tab of char, so to find the pixel we want,
// we are gonna find the right position in this tab, then we retrieve the pixel
// by taking all the four char wich represent rgba at once in a int.
// char = 8 bits, int = 32 bits. so casting an int to retrieve from a char tab,
// its gonna take four char at once (32 bits).
// the x is the column of the pixel we want, y is the line.
// to go from a line to the next one, we add line_length and not TEXTURE_WIDTH
// since the TEXTURE_WIDTH is equal to the number of pixel before next line,
// and line_length is equal to the number of char berfore next line.
unsigned int	get_texture_pixel(t_data *data, int x, int y, void *texture_adr)
{
	char			*pixel_addr;
	unsigned int	pixel_color;

	pixel_addr = texture_adr + (y * data->texture->line_length + x *
							data->texture->bits_per_pixel / 8);
	pixel_color = *(unsigned int *)pixel_addr;
	return (pixel_color);
}

// this function is mapping the wall to the texture.
// wich means finding the corresponding value from our position in the wall,
// to our position in the texture.
// after this being done, we can find the right pixel color we need.
void	get_right_pixel_tex(t_data *data, t_mlx *mlx, unsigned int wall_pixel,
														unsigned int wall_start)
{
	char	*texture_addr;

	texture_addr = right_texture_addr(data);
	find_tex_x(data);
	data->texture->tex_y = wall_pixel * data->texture->step;
	data->pixel_color = get_texture_pixel(data, data->texture->tex_x,
									data->texture->tex_y, texture_addr);
}

// to draw the pixel, we call the draw function with a string wich define the
// nature of the pixel (ceiling, wall, or floor).
// the texture step will give us the distance with the next pixel we need to
// copy.
void	draw_all_pixels(t_data *data, t_mlx *mlx, t_texture *texture,
						unsigned int wall_start, unsigned int wall_end)
{
	unsigned int	pixel;
	unsigned int	wall_pixel;

	pixel = 0;
	wall_pixel = 0;
	while (pixel < wall_start)
	{
		draw_pixel(data, mlx, "ceiling", 0);
		pixel++;
	}
	texture->step = (double)TEXTURE_HEIGHT / data->wall_pixel_height;
	while (pixel <= wall_end)
	{
		get_right_pixel_tex(data, texture, wall_pixel, wall_start);
		draw_pixel(data, mlx, "wall", pixel);
		wall_pixel++;
		pixel++;
	}
	while(pixel < WIN_HEIGHT)
	{
		draw_pixel(data, mlx, "floor", 0);
		pixel++;
	}
}

// the start of the wall will be at the center of the screen with substracting
// the the height of the wall with win_height, but we went to far, so we only
// keep the half of this result.
// by doing so, we start and stop exactly at the same distance from the center. 
void	pinpoint_wall_start_end(t_data *data, unsigned int *wall_start,
												unsigned int *wall_end)
{
	if (data->wall_pixel_height >= WIN_HEIGHT)
	{
		*wall_start = 0;
		*wall_end = WIN_HEIGHT - 1;
	}
	else
	{
		*wall_start = (WIN_HEIGHT - data->wall_pixel_height) / 2;
		*wall_end = *wall_start + data->wall_pixel_height - 1;
	}
}

// we don't use wall_dist, wich will create a fish eye. Instead we calculate
// the perpendicular distance with the main_ray.
// and we find the wall_height thanks to the win_height divided by the
// perp_wall_dist.
void	identify_wall_height(t_data *data)
{
	if (data->side = 0)
		data->perp_wall_dist = (data->map_x - data->pos_x +
						(1 - data->step_x) / 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->pos_y +
						(1 - data->step_y) / 2) / data->ray_dir_y;
	data->wall_pixel_height = (unsigned int)(WIN_HEIGHT / data->perp_wall_dist);
}

// First, find the right distance and deduct the wall height in pixel.
// we then deduct where the wall start and stop on the screen.
// a calcul must be done to know how much of the texture pixel we need, 100% of
// them ? 50% or 124.6518% ?
// and know we can take the right pixels of our texture, to print them on our
// screen img.
void	draw_column(t_data *data, t_mlx *mlx, t_texture *texture)
{
	unsigned int	wall_start;
	unsigned int	wall_end;

	wall_start = 0;
	wall_end = 0;
	identify_wall_height(data);
	pinpoint_wall_start_end(data, &wall_start, &wall_end);
	draw_all_pixels(data, mlx, texture, wall_start, wall_end);
}
