/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:50:27 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/22 17:51:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_forward(char **maze, t_player *game)
{
	double	new_pos_x;
	double	new_pos_y;
	double	y;

	y = game->pos_y;
	new_pos_x = game->pos_x + game->dir_x * MOVE_SPEED;
	if (maze[(int)y][(int)new_pos_x] && \
		maze[(int)y][(int)new_pos_x] != '1')
		game->pos_x = new_pos_x;
	new_pos_y = game->pos_y + game->dir_y * MOVE_SPEED;
	if (maze[(int)new_pos_y][(int)game->pos_x] && \
		maze[(int)new_pos_y][(int)game->pos_x] != '1')
		game->pos_y = new_pos_y;
}

void	move_backward(char **maze, t_player *game)
{
	double	new_pos_x;
	double	new_pos_y;
	double	y;

	y = game->pos_y;
	new_pos_x = game->pos_x - game->dir_x * MOVE_SPEED;
	if (maze[(int)y][(int)new_pos_x] && \
		maze[(int)y][(int)new_pos_x] != '1')
		game->pos_x = new_pos_x;
	new_pos_y = game->pos_y - game->dir_y * MOVE_SPEED;
	if (maze[(int)new_pos_y][(int)game->pos_x] && \
		maze[(int)new_pos_y][(int)game->pos_x] != '1')
		game->pos_y = new_pos_y;
}

void	move_right(char **maze, t_player *game)
{
	double	new_pos_x;
	double	new_pos_y;
	double	y;

	y = game->pos_y;
	new_pos_x = game->pos_x + game->plane_x * MOVE_SPEED;
	if (maze[(int)y][(int)new_pos_x] && \
		maze[(int)y][(int)new_pos_x] != '1')
		game->pos_x = new_pos_x;
	new_pos_y = game->pos_y + game->plane_y * MOVE_SPEED;
	if (maze[(int)new_pos_y][(int)game->pos_x] && \
		maze[(int)new_pos_y][(int)game->pos_x] != '1')
		game->pos_y = new_pos_y;
}

void	move_left(char **maze, t_player *game)
{
	double	new_pos_x;
	double	new_pos_y;
	double	y;

	y = game->pos_y;
	new_pos_x = game->pos_x - game->plane_x * MOVE_SPEED;
	if (maze[(int)y][(int)new_pos_x] && maze[(int)y][(int)new_pos_x] != '1')
		game->pos_x = new_pos_x;
	new_pos_y = game->pos_y - game->plane_y * MOVE_SPEED;
	if (maze[(int)new_pos_y][(int)game->pos_x] && \
		maze[(int)new_pos_y][(int)game->pos_x] != '1')
		game->pos_y = new_pos_y;
}

void	rotate(t_player *game, bool left)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = MOVE_SPEED;
	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	if (left == true)
		angle *= -1;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}
