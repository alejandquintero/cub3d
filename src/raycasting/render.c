/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:13:55 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/29 14:03:26 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_rgba(int *rgb, int op)
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | op);
}

void	render_col(t_structs *s, int x, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	rgb_walls[3];

	rgb_walls[0] = 169;
	rgb_walls[1] = 169;
	rgb_walls[2] = 169;
	line_height = (int)(HEIGHT / s->ray->perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = 0;
	while (y < draw_start)
		mlx_put_pixel(s->img, x, y++, get_rgba(s->cub3d->ceil_rgb, 255));
	while (y < draw_end)
		mlx_put_pixel(s->img, x, y++, get_rgba(rgb_walls, (128 * (side + 1))));
	while (y < HEIGHT)
		mlx_put_pixel(s->img, x, y++, get_rgba(s->cub3d->floor_rgb, 255));
}

void	render_view(void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	mlx_delete_image(s->mlx, s->img);
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	if (!s->img)
	{
		mlx_terminate(s->mlx);
		exit(EXIT_FAILURE);
	}
	raycasting_engine(s);
	mlx_image_to_window(s->mlx, s->img, 0, 0);
	mlx_key_hook(s->mlx, bind_keys, s);
}
