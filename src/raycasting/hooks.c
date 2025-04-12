/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:06:38 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/24 17:02:41 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	free_textures(t_structs *s)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (s->textures[i].img)
		{
			mlx_delete_image(s->mlx, s->textures[i].img);
			s->textures[i].img = NULL;
		}
		if (s->textures[i].texture)
		{
			mlx_delete_xpm42(s->textures[i].texture);
			s->textures[i].texture = NULL;
		}
		i++;
	}
}

void	close_window(void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	free_textures(s);
	if (s->img)
		mlx_delete_image(s->mlx, s->img);
	if (s->mlx)
		mlx_close_window(s->mlx);
	free_structs(s->cub3d, NULL);
	s->should_exit = true;
}

void	bind_keys(mlx_key_data_t keydata, void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window(s);
	else if (keydata.key == MLX_KEY_A)
		move(s->cub3d->maze, s->game, -s->game->plane_x, -s->game->plane_y);
	else if (keydata.key == MLX_KEY_D)
		move(s->cub3d->maze, s->game, s->game->plane_x, s->game->plane_y);
	else if (keydata.key == MLX_KEY_W)
		move(s->cub3d->maze, s->game, s->game->dir_x, s->game->dir_y);
	else if (keydata.key == MLX_KEY_S)
		move(s->cub3d->maze, s->game, -s->game->dir_x, -s->game->dir_y);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate(s->game, false);
	else if (keydata.key == MLX_KEY_LEFT)
		rotate(s->game, true);
}
