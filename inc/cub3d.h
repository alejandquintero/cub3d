/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:11:04 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/12 19:11:06 by lgandari         ###   ########.fr       */
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

# include "structs.h"
# include "parsing.h"
# include "raycasting.h"

# define WIDTH 1512
# define HEIGHT 982
# define MOVE_SPEED 0.09
# define ROTATION_SPEED 0.08
# define FOV 0.66

void	init_structs(t_cub3d *cub3d, t_file *file);
void	free_structs(t_cub3d *cub3d, t_file *file);
void	free_textures(t_structs *s);
void	free_llist(t_llist *llist);

#endif
