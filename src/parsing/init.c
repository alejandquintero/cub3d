/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:20:50 by lgandari          #+#    #+#             */
/*   Updated: 2025/02/28 20:27:27 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	cub3d->maze = NULL;
	cub3d->north_tex = NULL;
	cub3d->south_tex = NULL;
	cub3d->west_tex = NULL;
	cub3d->east_tex = NULL;
	cub3d->floor_rgb = NULL;
	cub3d->ceil_rgb = NULL;
	cub3d->player_pos = NULL;
}
