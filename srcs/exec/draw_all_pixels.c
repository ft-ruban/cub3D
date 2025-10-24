#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// the texture is contain in a linear tab of char, so to find the pixel we want,
// we are gonna find the right position in this tab, then we retrieve the pixel
// by taking all the four char wich represent rgba at once in a int.
// char = 8 bits, int = 32 bits. so casting an int to retrieve from a char tab,
// its gonna take four char at once (32 bits).
// the x is the column of the pixel we want, y is the line.
// to go from a line to the next one, we add line_length and not TEXTURE_WIDTH
// since the TEXTURE_WIDTH is equal to the number of pixel before next line,
// and line_length is equal to the number of char berfore next line.

unsigned int	get_texture_pixel(t_img *texture, int x, int y)
{
	char			*pixel_addr;
	unsigned int	pixel_color;

	pixel_addr = texture->addr + (y * texture->line_length + x *
							texture->bits_per_pixel / 8); // LDEV: BITSHIFT 3
	pixel_color = *(unsigned int *)pixel_addr;
	return (pixel_color);
}

// we first collect the exact hit position with the wall.
// this float value will be substract with the int version of himself, to keep
// the position within the wall only.
// then we adjust the value to where it match in the texture img.
// finally we flip the image texture if we face north or east.

void	find_texture_x(t_ray *ray, t_map *map, t_texture *texture)
{
	float	wall_hit_pos;

	if (ray->side == 0)
		wall_hit_pos = map->player_pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_hit_pos = map->player_pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_hit_pos -= (int)wall_hit_pos;
	texture->x = (int)(wall_hit_pos * TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0) ||
		(ray->side == 1 && ray->dir_y < 0))
	texture->x = TEXTURE_WIDTH - texture->x - 1;
}

// if side = 0, the wall enconter is on the x axe, so it is either the east or
// west texture.
// if side = 1, on the y axe, the texture will be the north or south one.

t_img	*right_texture_addr(t_ray *ray, t_texture *texture)
{
	t_img	*ptr_texture;

	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			ptr_texture = texture->we->img;
		else
			ptr_texture = texture->ea->img;
	}
	else
	{
		if (ray->dir_y < 0)
			ptr_texture = texture->so->img;
		else
			ptr_texture = texture->no->img;
	}
	return (ptr_texture);
}

// this function is mapping the wall to the texture.
// wich means finding the corresponding value from our position in the wall,
// to our position in the texture.
// after this being done, we can find the right pixel color we need.

void	get_right_pixel_tex(t_cub3d *cub3d, unsigned int wall_pixel)
{
	t_img	*texture_addr;

	texture_addr = right_texture_addr(cub3d->ray, cub3d->texture);
	find_texture_x(cub3d->ray, cub3d->map, cub3d->texture);
	cub3d->texture->y = wall_pixel * cub3d->texture->render;
	cub3d->texture->pixel_color = get_texture_pixel(texture_addr,
							cub3d->texture->x, cub3d->texture->y);
}

// to draw the pixel, we call the draw function with a string wich define the
// nature of the pixel (ceiling, wall, or floor).
// the texture step will give us the distance with the next pixel we need to
// copy.

void	draw_all_pixels(t_cub3d *cub3d, t_texture *texture,
				unsigned int wall_start, unsigned int wall_end)
{
	unsigned int	pixel;
	unsigned int	wall_pixel;

	pixel = 0;
	wall_pixel = 0;
	while (pixel < wall_start)
	{
		draw_one_pixel(cub3d->mlx, cub3d->texture->ceil_hex);
		pixel++;
	}
	texture->render = (double)TEXTURE_HEIGHT / texture->wall_pixel_height;
	while (pixel <= wall_end)
	{
		get_right_pixel_tex(cub3d, wall_pixel);
		draw_one_pixel(cub3d->mlx, texture->pixel_color);
		wall_pixel++;
		pixel++;
	}
	while(pixel < WIN_HEIGHT)
	{
		draw_one_pixel(cub3d->mlx, cub3d->texture->floor_hex);
		pixel++;
	}
}
