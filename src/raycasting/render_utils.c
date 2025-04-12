/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:15:24 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/12 19:15:33 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_rgba(int *rgb, int op)
{
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | op);
}

t_img	get_texture(t_structs *s, t_ray *ray, int side)
{
	if (side == 0 && ray->ray_dir_x <= 0)
		return (s->textures[3]);
	else if (side == 0 && ray->ray_dir_x > 0)
		return (s->textures[2]);
	else if (side == 1 && ray->ray_dir_y > 0)
		return (s->textures[1]);
	else
		return (s->textures[0]);
}

double	get_wall_hitpoint(t_structs *s, int side)
{
	if (side == 0)
		return ((s->game->pos_y + s->ray->perp_wall_dist * s->ray->ray_dir_y) - \
			floor(s->game->pos_y + s->ray->perp_wall_dist * s->ray->ray_dir_y));
	else
		return ((s->game->pos_x + s->ray->perp_wall_dist * s->ray->ray_dir_x) - \
			floor(s->game->pos_x + s->ray->perp_wall_dist * s->ray->ray_dir_x));
}

int	get_texture_x(t_structs *s, int side, int tex_width, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex_width);
	if ((side == 0 && s->ray->ray_dir_x < 0) || \
		(side == 1 && s->ray->ray_dir_y > 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

uint32_t	get_texture_color(t_img *tex, int tex_x, int tex_y)
{
	int	index;
	int	rgb[3];

	index = (tex->img->width * tex_y + tex_x) * 4;
	rgb[0] = tex->img->pixels[index];
	rgb[1] = tex->img->pixels[index + 1];
	rgb[2] = tex->img->pixels[index + 2];
	return (get_rgba(rgb, tex->img->pixels[index + 3]));
}
