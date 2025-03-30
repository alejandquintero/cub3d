/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:38:45 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/29 13:09:38 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_dir_vectors(t_player *game, t_cub3d *cub3d)
{
	if (cub3d->dir_player == 'N')
	{
		game->dir_y = -1;
		game->dir_x = 0;
	}
	else if (cub3d->dir_player == 'S')
	{
		game->dir_y = 1;
		game->dir_x = 0;
	}
	else if (cub3d->dir_player == 'E')
	{
		game->dir_y = 0;
		game->dir_x = 1;
	}
	else if (cub3d->dir_player == 'W')
	{
		game->dir_y = 0;
		game->dir_x = -1;
	}
}

static void	init_player(t_player *game, t_cub3d *cub3d)
{
	set_dir_vectors(game, cub3d);
	game->pos_x = cub3d->pos_player_x + 0.5;
	game->pos_y = cub3d->pos_player_y + 0.5;
	game->plane_x = game->dir_y * FOV * -1;
	game->plane_y = game->dir_x * FOV;
}

static void	setup_game_context(t_structs *s, t_cub3d *cub3d, \
	t_player *game, t_ray *ray)
{
	s->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!s->mlx)
		exit(EXIT_FAILURE);
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	if (!s->img)
	{
		mlx_terminate(s->mlx);
		exit(EXIT_FAILURE);
	}
	s->cub3d = cub3d;
	s->game = game;
	s->ray = ray;
	mlx_image_to_window(s->mlx, s->img, 0, 0);
}

bool	open_window(t_cub3d *cub3d)
{
	t_player	game;
	t_ray		ray;
	t_structs	s;

	init_player(&game, cub3d);
	setup_game_context(&s, cub3d, &game, &ray);
	mlx_key_hook(s.mlx, bind_keys, &s);
	mlx_close_hook(s.mlx, close_window, &s);
	mlx_loop_hook(s.mlx, game_loop, &s);
	mlx_loop(s.mlx);
	return (true);
}
