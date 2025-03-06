/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:20:50 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/06 21:07:55 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_tcub3d(t_cub3d *cub3d)
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
	cub3d->dir_player = '\0';
}

static void	init_tfile(t_file *file)
{
	if (!file)
		return ;
	file->valid_ids[0] = "NO";
	file->valid_ids[1] = "EA";
	file->valid_ids[2] = "WE";
	file->valid_ids[3] = "SO";
	file->valid_ids[4] = "F";
	file->valid_ids[5] = "C";
	file->valid_ids[6] = NULL;
}

void	init_structs(t_cub3d *cub3d, t_file *file)
{
	init_tcub3d(cub3d);
	init_tfile(file);
}
