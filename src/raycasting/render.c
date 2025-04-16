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

static t_draw_params	compute_draw_params(t_structs *s)
{
	t_draw_params	params;

	params.line_height = (int)(HEIGHT / s->ray->perp_wall_dist);
	params.draw_start = -params.line_height / 2 + HEIGHT / 2;
	params.draw_end = params.line_height / 2 + HEIGHT / 2;
	if (params.draw_start < 0)
		params.draw_start = 0;
	if (params.draw_end >= HEIGHT)
		params.draw_end = HEIGHT;
	return (params);
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

static void	draw_background(t_structs *s, int x, int start_y, int *rgb)
{
	int	y;

	if (x < 0 || x >= WIDTH || start_y < 0 || start_y >= HEIGHT)
		return ;
	if (!rgb)
		return ;
	y = start_y;
	while (y < HEIGHT)
	{
		mlx_put_pixel(s->img, x, y, get_rgba(rgb, 255));
		y++;
	}
}

void	render_col(t_structs *s, int x, int side)
{
	t_draw_params	params;

	params = compute_draw_params(s);
	draw_background(s, x, 0, s->cub3d->ceil_rgb);
	render_tex(s, side, x, params);
	draw_background(s, x, params.draw_end, s->cub3d->floor_rgb);
}

void	game_loop(void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	handle_mouse_rotation(s);
	if (s->should_exit || s->cub3d == NULL || s->cub3d->maze == NULL)
		return ;
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
		move(s->cub3d->maze, s->game, s->game->dir_x, s->game->dir_y);
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
		move(s->cub3d->maze, s->game, -s->game->dir_x, -s->game->dir_y);
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
		move(s->cub3d->maze, s->game, -s->game->plane_x, -s->game->plane_y);
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
		move(s->cub3d->maze, s->game, s->game->plane_x, s->game->plane_y);
	if (mlx_is_key_down(s->mlx, MLX_KEY_LEFT))
		rotate(s->game, true);
	if (mlx_is_key_down(s->mlx, MLX_KEY_RIGHT))
		rotate(s->game, false);
	if (mlx_is_key_down(s->mlx, MLX_KEY_ESCAPE))
		close_window(s);
	else
		raycasting_engine(s);
}
