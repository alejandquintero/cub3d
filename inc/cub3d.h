/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:39:44 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/03 23:42:42 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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
	int		*player_pos;
}	t_cub3d;

void	free_file(t_file *file);
void	free_cub3d(t_cub3d *cub3d);

void	parse_maze(char *maze_path, t_file *file, t_cub3d *cub3d);
bool	extract_metadata(t_file *file, t_cub3d *cub3d);

void	init_cub3d(t_cub3d *cub3d);

bool	is_space(char c);
bool	is_valid_id(const char *id, const char **valid_ids);
bool	is_valid_texture(const char *path);
bool	is_valid_rgb_str(const char *str, int *rgb_num);
bool	is_valid_maze(char *cursor);

bool	store_texture(t_cub3d *cub3d, const char *id, char *path);
bool	store_color(t_cub3d *cub3d, const char *id, char *rgb_str);

#endif
