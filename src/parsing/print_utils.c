/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:01:53 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/21 17:47:43 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	print_texture(const char *name, const char *texture)
{
	if (texture)
		printf("%s Texture: %s\n", name, texture);
	else
		printf("%s Texture: NULL\n", name);
}

static void	print_color(const char *name, int *color)
{
	if (color)
		printf("%s Color: [%d, %d, %d]\n", name, color[0], color[1], color[2]);
	else
		printf("%s Color: NULL\n", name);
}

static void	print_maze(char **maze, int i)
{
	if (maze)
	{
		printf("Maze:\n");
		while (maze[i])
			printf("%s\n", maze[i++]);
	}
	else
		printf("Maze: NULL\n");
}

static void	print_direction(char dir_player)
{
	if (dir_player)
		printf("Direction of player: %c\n", dir_player);
	else
		printf("Direction of player: NULL\n");
}

void	print_cub3d(const t_cub3d *cub3d)
{
	int	i;

	i = 0;
	printf("--- BEGIN OF STRUCT DATA ---\n");
	print_texture("North", cub3d->north_tex);
	print_texture("South", cub3d->south_tex);
	print_texture("West", cub3d->west_tex);
	print_texture("East", cub3d->east_tex);
	print_color("Floor", cub3d->floor_rgb);
	print_color("Ceiling", cub3d->ceil_rgb);
	print_maze(cub3d->maze, i);
	print_direction(cub3d->dir_player);
	printf("--- END OF STRUCT DATA ---\n");
}
