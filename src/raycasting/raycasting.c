/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:16:05 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/22 14:05:03 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	update_ray(t_ray *ray, t_player *game, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	else
		ray->delta_dist_x = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	else
		ray->delta_dist_y = 1e30;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
}

static int	perform_dda(t_ray *ray, t_cub3d *cub3d)
{
	int	hit;
	int	side;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (cub3d->maze[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (side);
}

static void	setup_ray_direction_steps(t_ray *ray, t_player *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->pos_y) * ray->delta_dist_y;
	}
}

void	raycasting_engine(void *param)
{
	int			x;
	int			side;
	t_ray		ray;
	t_structs	*s;

	x = -1;
	s = (t_structs *)param;
	while (++x < WIDTH)
	{
		update_ray(&ray, s->game, x);
		setup_ray_direction_steps(&ray, s->game);
		side = perform_dda(&ray, s->cub3d);
		if (side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
		render_col(s->img, x, side, ray.perp_wall_dist);
	}
	mlx_key_hook(s->mlx, close_on_esc, s->mlx);
	mlx_image_to_window(s->mlx, s->img, 0, 0);
}
