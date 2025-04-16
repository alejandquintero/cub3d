/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:34:04 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/12 19:34:05 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <stdbool.h>
# include "structs.h"

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_y;
	double	dir_x;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
}	t_ray;

typedef struct s_img
{
	xpm_t		*texture;
	mlx_image_t	*img;
}	t_img;

typedef struct s_structs
{
	struct s_cub3d	*cub3d;
	struct s_player	*game;
	struct s_ray	*ray;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_img			textures[4];
	bool			should_exit;
	int				last_mouse_x;
}	t_structs;

typedef struct s_draw_params
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_draw_params;

typedef struct s_texture_info
{
	t_img	tex;
	int		width;
	int		height;
	int		tex_x;
}	t_texture_info;

typedef struct s_texture_mapping
{
	double	wall_hit;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		screen_y;
}	t_texture_mapping;

// Movement and rotation
void		move(char **maze, t_player *game, double x, double y);
void		rotate(t_player *game, bool left);

// Raycasting engine
void		raycasting_engine(t_structs *s);
void		render_col(t_structs *s, int x, int side);

// Hooks
bool		open_window(t_cub3d *cub3d);
void		close_window(void *param);
void		bind_keys(mlx_key_data_t keydata, void *param);
void		game_loop(void *param);

// Textures
uint32_t	get_rgba(int *rgb, int op);
t_img		get_texture(t_structs *s, t_ray *ray, int side);
double		get_wall_hitpoint(t_structs *s, int side);
int			get_texture_x(t_structs *s, int side, int tex_width, double wall_x);
uint32_t	get_texture_color(t_img *tex, int tex_x, int tex_y);

#endif
