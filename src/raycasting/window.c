/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:38:45 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/23 17:07:48 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_player(t_player *game, t_cub3d *cub3d)
{
	game->pos_x = cub3d->dir_player_x + 0.5;
	game->pos_y = cub3d->dir_player_y + 0.5;
	game->dir_y = 0;
	game->dir_x = -1;
	game->plane_x = game->dir_y * FOV;
	game->plane_y = game->dir_x * FOV;
}

bool	open_window(t_cub3d *cub3d)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	game;
	t_ray		ray;
	t_structs	s;

	init_player(&game, cub3d);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		exit(EXIT_FAILURE);
	}
	s.cub3d = cub3d;
	s.img = img;
	s.mlx = mlx;
	s.game = &game;
	s.ray = &ray;
	mlx_loop_hook(mlx, render_view, &s);
	mlx_loop(mlx);
	return (true);
}
