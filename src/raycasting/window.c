/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:16:49 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/20 22:50:31 by aquinter         ###   ########.fr       */
/*                                                                            */
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

bool	open_window(t_cub3d *cub3d)
{
	// x and y start position (player)
	double	pos_x = cub3d->dir_player_x + 0.5;
	double	pos_y = cub3d->dir_player_y + 0.5;

	// Initial direction vector (W in this case)
	double	dir_y = 0;
	double	dir_x = -1;

	// Camera plane, 0.66 is FOV (constant)
	double	plane_x = dir_y * 0.66;
	double	plane_y = dir_x * 0.66;

	// Init mlx
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    if (!mlx)
		exit(EXIT_FAILURE);

	// Init image
	mlx_image_t	*img = mlx_new_image(mlx, WIDTH, HEIGHT);

	// Init raycasting
	int x = 0;
	while (x < WIDTH)
	{
		// Calculate ray position and direction
		double	camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
		double	ray_dir_x = dir_x + plane_x * camera_x;
		double	ray_dir_y = dir_y + plane_y * camera_x;

		// Which box of the map we're in
		int	map_x = (int)pos_x;
		int	map_y = (int)pos_y;

		// Length of ray from current position to next x or y-side
		double	side_dist_x = 0;
		double	side_dist_y = 0;

		// Length of ray from one x or y-side to next x or y-side	
		double	delta_dist_x  = 1e30;
		if (ray_dir_x != 0)
			delta_dist_x = fabs(1 / ray_dir_x);

		double	delta_dist_y = 1e30;
		if (ray_dir_y != 0)
			delta_dist_y = fabs(1 / ray_dir_y);

		// Perpendicular distance from camera plane to the wall
		double	perp_wall_dist;

		// what direction to step in x or y-direction (either +1 or -1)
		int	step_x;
		int	step_y;

		int	hit = 0; // was there a wall hit?
		int	side; //was a NS or a EW wall hit?

		// Calculate step an initial side_dist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}
		// DDA
		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (cub3d->maze[map_y][map_x] == '1')
				hit = 1;
		}
		// Calculate distance projected on camera direction
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;

		// Calculate height of line to draw on screen
		int	line_height = (int)(HEIGHT / perp_wall_dist);

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
		x++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, close_on_esc, mlx);
    mlx_loop(mlx);
    return (true);
}
