/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   render.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aquinter <aquinter@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/21 18:13:55 by lgandari		  #+#	#+#			 */
/*   Updated: 2025/04/08 22:00:47 by aquinter		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_rgba(int *rgb, int op)
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | op);
}

t_img	get_texture(t_structs *s, t_ray *ray, int side)
{
	if (side == 0 && ray->ray_dir_x <= 0)
		return (s->textures[3]);
	else if (side == 0 && ray->ray_dir_x > 0)
		return (s->textures[2]);
	else if (side == 1 && ray->ray_dir_y > 0)
		return (s->textures[1]);
	else
		return (s->textures[0]);
}

static double	get_wall_hitpoint(t_structs *s, int side)
{
	if (side == 0)
		return ((s->game->pos_y + s->ray->perp_wall_dist * s->ray->ray_dir_y) - \
			floor(s->game->pos_y + s->ray->perp_wall_dist * s->ray->ray_dir_y));
	else
		return ((s->game->pos_x + s->ray->perp_wall_dist * s->ray->ray_dir_x) - \
			floor(s->game->pos_x + s->ray->perp_wall_dist * s->ray->ray_dir_x));
}

static int	get_texture_x(t_structs *s, int side, int tex_width, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex_width);
	if ((side == 0 && s->ray->ray_dir_x < 0) || \
		(side == 1 && s->ray->ray_dir_y > 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

static uint32_t	get_texture_color(t_img *tex, int tex_x, int tex_y)
{
	int	index;
	int	rgb[3];

	index = (tex->img->width * tex_y + tex_x) * 4;
	rgb[0] = tex->img->pixels[index];
	rgb[1] = tex->img->pixels[index + 1];
	rgb[2] = tex->img->pixels[index + 2];
	return (get_rgba(rgb, tex->img->pixels[index + 3]));
}

static t_draw_params	compute_draw_params(t_structs *s)
{
	t_draw_params	params;

	params.line_height = (int)(HEIGHT / s->ray->perp_wall_dist);
	params.draw_start = -params.line_height / 2 + HEIGHT / 2;
	params.draw_end = params.line_height / 2 + HEIGHT / 2;
	if (params.draw_start < 0)
		params.draw_start = 0;
	if (params.draw_end >= HEIGHT)
		params.draw_end = HEIGHT - 1;
	return (params);
}

static void	draw_ceiling(t_structs *s, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
		mlx_put_pixel(s->img, x, y++, get_rgba(s->cub3d->ceil_rgb, 255));
}

static void	draw_floor(t_structs *s, int x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < HEIGHT)
		mlx_put_pixel(s->img, x, y++, get_rgba(s->cub3d->floor_rgb, 255));
}

static void	render_tex(t_structs *s, int side, int x, t_draw_params params)
{
	t_texture_info		tex_info;
	t_texture_mapping	mapping;

	tex_info.tex = get_texture(s, s->ray, side);
	tex_info.width = tex_info.tex.img->width;
	tex_info.height = tex_info.tex.img->height;
	mapping.wall_hit = get_wall_hitpoint(s, side);
	tex_info.tex_x = get_texture_x(s, side, tex_info.width, mapping.wall_hit);
	mapping.step = 1.0 * tex_info.height / params.line_height;
	mapping.tex_pos = (params.draw_start - HEIGHT / 2 + \
		params.line_height / 2) * mapping.step;
	mapping.screen_y = params.draw_start;
	while (mapping.screen_y < params.draw_end)
	{
		mapping.tex_y = (int)mapping.tex_pos;
		mapping.tex_pos += mapping.step;
		mlx_put_pixel(s->img, x, mapping.screen_y, \
			get_texture_color(&tex_info.tex, tex_info.tex_x, mapping.tex_y));
		mapping.screen_y++;
	}
}

void	render_col(t_structs *s, int x, int side)
{
	t_draw_params	params;

	params = compute_draw_params(s);
	draw_ceiling(s, x, params.draw_start);
	render_tex(s, side, x, params);
	draw_floor(s, x, params.draw_end);
}

void	game_loop(void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	raycasting_engine(s);
}
