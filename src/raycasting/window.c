/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   window.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aquinter <aquinter@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/19 20:16:49 by aquinter		  #+#	#+#			 */
/*   Updated: 2025/03/20 22:50:31 by aquinter		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#define WIDTH 1512
#define HEIGHT 982

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	close_on_esc(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = NULL;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx = (mlx_t *)param;
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
}

static void	init_game(t_game *game, t_cub3d *cub3d)
{
	game->pos_x = cub3d->dir_player_x + 0.5;
	game->pos_y = cub3d->dir_player_y + 0.5;
	game->dir_y = 0;
	game->dir_x = -1;
	game->plane_x = game->dir_y * 0.66;
	game->plane_y = game->dir_x * 0.66;
}

static void	update_ray(t_ray *ray, t_game *game, int x)
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
}

bool	open_window(t_cub3d *cub3d)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_game		game;
	t_ray		ray;
	int			x;

	init_game(&game, cub3d);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		exit(EXIT_FAILURE);
	}
	x = -1;
	while (++x < WIDTH)
	{
		update_ray(&ray, &game, x);
		// Which box of the map we're in
		int	map_x = (int)game.pos_x;
		int	map_y = (int)game.pos_y;
		// Calculate step an initial side_dist
		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (game.pos_x - map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (map_x + 1.0 - game.pos_x) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (game.pos_y - map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (map_y + 1.0 - game.pos_y) * ray.delta_dist_y;
		}
		// DDA
		int	hit = 0;
		int	side;
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				map_x += ray.step_x;
				side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				map_y += ray.step_y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (cub3d->maze[map_y][map_x] == '1')
				hit = 1;
		}
		// Calculate distance projected on camera direction
		if (side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
		// Calculate height of line to draw on screen
		int	line_height = (int)(HEIGHT / ray.perp_wall_dist);
		// Calculate lowest and highest pixel to fill in current stripe
		int	draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		// Print line
		int y = 0;
		int opacity = 255;
		if (side == 1)
			opacity = opacity / 2;
		// Ceiling
		while (y < draw_start)
		{
			mlx_put_pixel(img, x, y, get_rgba(173, 216, 230, 255));
			y++;
		}
		// Walls
		while (y < draw_end)
		{
			mlx_put_pixel(img, x, y, get_rgba(169, 169, 169, opacity));
			y++;
		}
		// Floor
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, get_rgba(152, 251, 152, 255));
			y++;
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, close_on_esc, mlx);
	mlx_loop(mlx);
	return (true);
}
