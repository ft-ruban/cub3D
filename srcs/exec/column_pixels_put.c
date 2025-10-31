#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// 1) The texture is in a linear tab of char, so to find the pixel we want,
//    we are gonna find the right position in this tab, then we retrieve the
//    pixel by taking all the four char wich represent rgba at once in a int.
//    Char = 8 bits, int = 32 bits. so casting an int to retrieve from a char
//    tab, its gonna take four char at once (32 bits).
// 2) The x is the column of the pixel we want, y is the line.
//    To go from a line to the next one, we add line_length and not 
//    TEXTURE_WIDTH since the TEXTURE_WIDTH is equal to the number of pixel 
//    before next line, and line_length is equal to the number of char berfore
//    next line.

static unsigned int	get_texture_pixel(t_img *texture, int x, int y)
{
	char			*pixel_addr;
	unsigned int	pixel_color;

	pixel_addr = texture->addr + (y * texture->line_length + x
			* (int)(texture->bits_per_pixel));
	pixel_color = *(unsigned int *)pixel_addr;
	return (pixel_color);
}

// 1) Collect the exact hit position with the wall, either on the x axe or the
//    y one.
//    From the player position, we travel perp_dist_wall distance, in the x
//    or y direction.
// 2) We now have a value like 5.68 on one of the axes. And to find our place in
//    the texture we need a number in between 1 and 0, to know where we are on
//    the tile. so we substract 5.68 by himself, but the int version of it, wich
//    give us exactly what we need: 5.68 - 5 = 0.68.
// 3) Then we adapt this value to our TEXTURE_WIDTH.
//    Let's say TEXTURE_WIDTH is 200: 0.68 * 200 = 136. So we will take a pixel
//    on the 136th column.
//
// If we face the east or north texture, we have to revert the way we print
// the columns(x), so the texture appears in right.
// Basicaly if texture is 200 and x is 136, our new x valu is:
// 200 - 136 - 1 = 63.
// The "- 1" is here because the case 200 - 200 is not possible, but we still
// want to reach x = 0 if needed.

static void	find_texture_x(t_ray *ray, t_map *map, t_texture *texture)
{
	float	wall_hit_pos;

	if (ray->side == 0)
		wall_hit_pos = map->player_pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_hit_pos = map->player_pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_hit_pos -= (int)wall_hit_pos;
	texture->x = (int)(wall_hit_pos * TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		texture->x = TEXTURE_WIDTH - texture->x - 1;
}

// 1) There are 4 textures available, so let's find the one we need.
// 2) If side = 0, the wall enconter is on the x axe, so it is either the east
//    or west texture.
//    If side = 1, on the y axe, the texture will be the north or south one.
// 3) Finally, depending on if we look left(< 0) or right(> 0), we choose either
//    west/south texture, either east/north one.

static t_img	*right_texture(t_ray *ray, t_texture *texture)
{
	t_img	*ptr_texture;

	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			ptr_texture = texture->we;
		else
			ptr_texture = texture->ea;
	}
	else
	{
		if (ray->dir_y < 0)
			ptr_texture = texture->so;
		else
			ptr_texture = texture->no;
	}
	return (ptr_texture);
}

// 1) We point to the right texture addr (no, so, we and ea).
// 2) Then, to point on the exact pixel we want, we look out for the x and y
//    position needed.
// 3) Finding x will be the "find_texture_x" job, and y is simply obtained:
//    multiply the pixel we are at on the wall (1 being the first one,
//    wall_height being the last one) by the render value.
//    If y is 0 and render 2.15, then the first pixel_wall will correspond to
//    the texture_pixel line number 0. if y is 1, we will take the 2.15 line (2)
//    and so on until the end of the wall.
//
// The mecanic we use here with a render valu is called "mapping".
// Wich means finding the corresponding value from our position in the wall,
// to our position in the texture.
// After this being done, we can find the right pixel color we need.

static void	get_right_pixel_texture(t_cub3d *cub3d, unsigned int wall_pixel)
{
	t_img	*texture_addr;

	texture_addr = right_texture(cub3d->ray, cub3d->texture);
	find_texture_x(cub3d->ray, cub3d->map, cub3d->texture);
	cub3d->texture->y = (wall_pixel + cub3d->texture->offset)
		* cub3d->texture->render;
	cub3d->texture->pixel_color = get_texture_pixel(texture_addr,
			cub3d->texture->x, cub3d->texture->y);
}

// 1) To keep track of the pixel(or the wall pixel) we are currently working on,
//    it incremente itself everytime it is being draw. 
// 2) the texture render will give us the distance with the next pixel we need
//    to copy.
//    If we are close to the wall, we might want to re use the same pixel
//    texture, but when far away from one, we should skip some of them.

void	column_pixels_put(t_cub3d *cub3d, t_texture *texture,
				unsigned int wall_start, unsigned int wall_end)
{
	unsigned int	pixel;
	unsigned int	wall_pixel;

	pixel = 0;
	wall_pixel = 0;
	while (pixel < wall_start)
	{
		my_mlx_pixel_put(cub3d->mlx, texture->ceil_hex, cub3d->curr_column,
			pixel);
		pixel++;
	}
	while (pixel <= wall_end)
	{
		get_right_pixel_texture(cub3d, wall_pixel);
		my_mlx_pixel_put(cub3d->mlx, texture->pixel_color, cub3d->curr_column,
			pixel);
		wall_pixel++;
		pixel++;
	}
	while (pixel < WIN_HEIGHT)
	{
		my_mlx_pixel_put(cub3d->mlx, texture->floor_hex, cub3d->curr_column,
			pixel);
		pixel++;
	}
}
