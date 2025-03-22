/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:50:27 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/22 15:59:48 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_x(char **maze, t_player *game, bool forward)
{
	double	new_pos_x;
	double	y;

	y = game->pos_y;
	new_pos_x = game->pos_x - game->dir_x * MOVE_SPEED;
	if (forward == true)
		new_pos_x = game->pos_x + game->dir_x * MOVE_SPEED;
	if (maze[(int)y][(int)new_pos_x] && maze[(int)y][(int)new_pos_x] != '1')
		game->pos_x = new_pos_x;
}

void	move_y(char **maze, t_player *game, bool left)
{
	double	x;
	double	new_pos_y;

	x = game->pos_y;
	new_pos_y = game->pos_y - game->dir_y * MOVE_SPEED;
	if (left == true)
		new_pos_y = game->pos_y + game->dir_y * MOVE_SPEED;
	if (maze[(int)new_pos_y][(int)x] && maze[(int)new_pos_y][(int)x] != '1')
		game->pos_y = new_pos_y;
	printf("aquiiii\n");
}
