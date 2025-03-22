/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:13:55 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/22 16:15:12 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	render_col(mlx_image_t *img, int x, int side, double perp_wall_dist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	opacity;

	line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (side == 1)
		opacity = 128;
	else
		opacity = 255;
	y = 0;
	while (y < draw_start)
		mlx_put_pixel(img, x, y++, get_rgba(173, 216, 230, 255));
	while (y < draw_end)
		mlx_put_pixel(img, x, y++, get_rgba(169, 169, 169, opacity));
	while (y < HEIGHT)
		mlx_put_pixel(img, x, y++, get_rgba(152, 251, 152, 255));
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
