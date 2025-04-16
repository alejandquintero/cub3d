/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:54:37 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/16 23:54:55 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	rotate_view(t_player *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	handle_mouse_rotation(t_structs *s)
{
	int		mouse_x;
	int		mouse_y;
	int		delta_x;
	double	angle;

	mlx_get_mouse_pos(s->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - s->last_mouse_x;
	if (delta_x == 0)
		return ;
	angle = delta_x * MOUSE_SENSITIVITY;
	rotate_view(s->game, angle);
	s->last_mouse_x = mouse_x;
}
