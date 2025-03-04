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

static void	free_tfile(t_file *file)
{
	if (!file)
		return ;
	if (file->content)
	{
		free(file->content);
		file->content = NULL;
	}
}

static void	free_tcub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->maze)
		free_matrix(cub3d->maze);
	if (cub3d->north_tex)
		free(cub3d->north_tex);
	if (cub3d->south_tex)
		free(cub3d->south_tex);
	if (cub3d->west_tex)
		free(cub3d->west_tex);
	if (cub3d->east_tex)
		free(cub3d->east_tex);
	if (cub3d->floor_rgb)
		free(cub3d->floor_rgb);
	if (cub3d->ceil_rgb)
		free(cub3d->ceil_rgb);
	cub3d->maze = NULL;
	cub3d->north_tex = NULL;
	cub3d->south_tex = NULL;
	cub3d->west_tex = NULL;
	cub3d->east_tex = NULL;
	cub3d->floor_rgb = NULL;
	cub3d->ceil_rgb = NULL;
}

void	free_structs(t_cub3d *cub3d, t_file *file)
{
	free_tfile(file);
	free_tcub3d(cub3d);
}
