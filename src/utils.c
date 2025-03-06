/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/04 22:24:27 by lgandari		  #+#	#+#			 */
/*   Updated: 2025/03/04 22:25:38 by lgandari		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

// Delete this in the future + delete from .h
void	print_cub3d(const t_cub3d *cub3d)
{
	int	i;

	i = 0;
	printf("--- BEGIN OF STRUCT DATA ---\n");
	printf("North Texture: %s\n", cub3d->north_tex ? cub3d->north_tex : "NULL");
	printf("South Texture: %s\n", cub3d->south_tex ? cub3d->south_tex : "NULL");
	printf("West Texture: %s\n", cub3d->west_tex ? cub3d->west_tex : "NULL");
	printf("East Texture: %s\n", cub3d->east_tex ? cub3d->east_tex : "NULL");
	if (cub3d->floor_rgb)
		printf("Floor Color: [%d, %d, %d]\n", cub3d->floor_rgb[0], \
			cub3d->floor_rgb[1], cub3d->floor_rgb[2]);
	else
		printf("Floor Color: NULL\n");
	if (cub3d->ceil_rgb)
		printf("Ceiling Color: [%d, %d, %d]\n", cub3d->ceil_rgb[0], \
			cub3d->ceil_rgb[1], cub3d->ceil_rgb[2]);
	else
		printf("Ceiling Color: NULL\n");
	if (cub3d->maze)
	{
		printf("Maze:\n");
		while (cub3d->maze[i])
			printf("%s\n", cub3d->maze[i++]);
	}
	else
		printf("Maze: NULL\n");
	if (cub3d->dir_player)
		printf("Direction of player: %c\n", cub3d->dir_player);
	else
		printf("Direction of player: NULL\n");
	printf("--- END OF STRUCT DATA ---\n");
}
