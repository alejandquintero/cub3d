/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:50:27 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/24 17:05:14 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move(char **maze, t_player *game, double x, double y)
{
	double	new_pos_x;
	double	new_pos_y;
	double	check_pos_x;
	double	check_pos_y;

	new_pos_x = game->pos_x + x * MOVE_SPEED;
	new_pos_y = game->pos_y + y * MOVE_SPEED;
	if (x > 0)
		check_pos_x = new_pos_x + MARGIN;
	else
		check_pos_x = new_pos_x - MARGIN;
	if (maze[(int)game->pos_y][(int)check_pos_x] != '1')
		game->pos_x = new_pos_x;
	if (y > 0)
		check_pos_y = new_pos_y + MARGIN;
	else
		check_pos_y = new_pos_y - MARGIN;
	if (maze[(int)check_pos_y][(int)game->pos_x] != '1')
		game->pos_y = new_pos_y;
}

void	rotate(t_player *game, bool left)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = ROTATION_SPEED;
	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	if (left == true)
		angle *= -1;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}
