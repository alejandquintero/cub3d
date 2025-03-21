/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:39:44 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/20 22:43:28 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft_v2/inc/libft.h"
# include "../libft_v2/inc/extra.h"
# include "../libft_v2/inc/get_next_line.h"

typedef struct s_file
{
	const char	*valid_ids[7];
	char		*content;
}	t_file;

typedef struct s_cub3d
{
	char	**maze;
	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;
	int		*floor_rgb;
	int		*ceil_rgb;
	int		dir_player_x;
	int		dir_player_y;
	char	dir_player;
}	t_cub3d;

typedef struct s_llist
{
	struct s_llist	*next;
	char			*line;
}	t_llist;

typedef struct	s_game
{
	double	pos_x;
	double	pos_y;
	double	dir_y;
	double	dir_x;
	double	plane_x;
	double	plane_y;
}	t_game;

typedef struct	s_ray
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
}	t_ray;

void	init_structs(t_cub3d *cub3d, t_file *file);
void	free_structs(t_cub3d *cub3d, t_file *file);
void	free_llist(t_llist *llist);
void	print_cub3d(const t_cub3d *cub3d);

void	parse_maze(char *maze_path, t_file *file, t_cub3d *cub3d);
void	initialize_positions(int positions[8][2], int i, int j);
bool	append_llist(t_llist **llist, char *line);
bool	extract_metadata(t_file *file, t_cub3d *cub3d);
bool	extract_maze(t_cub3d *cub3d, char *cursor);

char	**llist_to_array(t_llist *llist);

char	*extract_line(char **str);

bool	is_space(char c);
bool	is_valid_id(const char *id, const char **valid_ids);
bool	store_texture(t_cub3d *cub3d, const char *id, char *path);
bool	store_color(t_cub3d *cub3d, const char *id, char *rgb_str);
bool	is_invalid_char(char c);
bool	is_player(char c);
bool	is_allowed_char(char c);

bool	open_window(t_cub3d *cub3d);

#endif
