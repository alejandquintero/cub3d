/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/23 12:55:50 by lgandari		  #+#	#+#			 */
/*   Updated: 2025/02/23 12:55:52 by lgandari		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_file(t_file *file)
{
	if (!file)
		return ;
	if (file->content)
	{
		free(file->content);
		file->content = NULL;
	}
}

void	free_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->maze)
	{
		free_matrix(cub3d->maze);
		cub3d->maze = NULL;
	}
	if (cub3d->north_tex)
	{
		free(cub3d->north_tex);
		cub3d->north_tex = NULL;
	}
	if (cub3d->south_tex)
	{
		free(cub3d->south_tex);
		cub3d->south_tex = NULL;
	}
	if (cub3d->west_tex)
	{
		free(cub3d->west_tex);
		cub3d->west_tex = NULL;
	}
	if (cub3d->east_tex)
	{
		free(cub3d->east_tex);
		cub3d->east_tex = NULL;
	}
	if (cub3d->floor_rgb)
	{
		free(cub3d->floor_rgb);
		cub3d->floor_rgb = NULL;
	}
	if (cub3d->ceil_rgb)
	{
		free(cub3d->ceil_rgb);
		cub3d->ceil_rgb = NULL;
	}
}
