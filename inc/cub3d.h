/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:39:44 by aquinter          #+#    #+#             */
/*   Updated: 2025/02/27 20:30:07 by aquinter         ###   ########.fr       */
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

void	parse_maze(char *maze_path, t_file *file);
void	free_file(t_file *file);
bool	extract_metadata(t_file *file);

#endif