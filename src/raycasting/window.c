/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:38:45 by aquinter          #+#    #+#             */
/*   Updated: 2025/04/15 20:10:34 by aquinter         ###   ########.fr       */
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

bool	load_textures(t_structs *s)
{
	int	i;

	s->textures[0].texture = mlx_load_xpm42(s->cub3d->north_tex);
	s->textures[1].texture = mlx_load_xpm42(s->cub3d->south_tex);
	s->textures[2].texture = mlx_load_xpm42(s->cub3d->east_tex);
	s->textures[3].texture = mlx_load_xpm42(s->cub3d->west_tex);
	i = 0;
	while (i < 4)
	{
		if (!s->textures[i].texture)
			return (print_error("Error\nFailed to load texture.\n", false), \
				false);
		s->textures[i].img = mlx_texture_to_image(s->mlx, \
			&s->textures[i].texture->texture);
		if (!s->textures[i].img)
			return (print_error("Error\nFailed to convert texture.\n", false), \
				false);
		i++;
	}
	return (true);
}

static void	setup_game_context(t_structs *s, t_cub3d *cub3d, \
	t_player *game, t_ray *ray)
{
	s->cub3d = cub3d;
	s->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!s->mlx)
		exit(EXIT_FAILURE);
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	if (!load_textures(s))
	{
		mlx_terminate(s->mlx);
		exit(EXIT_FAILURE);
	}
	if (!s->img)
	{
		mlx_terminate(s->mlx);
		exit(EXIT_FAILURE);
	}
	s->cub3d = cub3d;
	s->game = game;
	s->ray = ray;
	s->should_exit = false;
	mlx_image_to_window(s->mlx, s->img, 0, 0);
}

bool	open_window(t_cub3d *cub3d)
{
	t_player	game;
	t_ray		ray;
	t_structs	s;

	init_player(&game, cub3d);
	setup_game_context(&s, cub3d, &game, &ray);
	mlx_close_hook(s.mlx, close_window, &s);
	mlx_loop_hook(s.mlx, game_loop, &s);
	mlx_loop(s.mlx);
	free_textures(&s);
	if (s.img)
		mlx_delete_image(s.mlx, s.img);
	if (s.mlx)
		mlx_terminate(s.mlx);
	free_structs(s.cub3d, NULL);
	return (true);
}
