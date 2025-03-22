/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:06:38 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/22 17:27:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	close_window(mlx_t *mlx)
{
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}

void	bind_keys(mlx_key_data_t keydata, void *param)
{
	t_structs	*s;

	s = (t_structs *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window(s->mlx);
	else if (keydata.key == MLX_KEY_A)
		move_left(s->cub3d->maze, s->game);
	else if (keydata.key == MLX_KEY_D)
		move_right(s->cub3d->maze, s->game);
	else if (keydata.key == MLX_KEY_W)
		move_forward(s->cub3d->maze, s->game);
	else if (keydata.key == MLX_KEY_S)
		move_backward(s->cub3d->maze, s->game);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate(s->game, false);
	else if (keydata.key == MLX_KEY_LEFT)
		rotate(s->game, true);
}
