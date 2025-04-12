/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:36 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/12 20:01:37 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int		pos_player_x;
	int		pos_player_y;
	char	dir_player;
}	t_cub3d;

typedef struct s_llist
{
	struct s_llist	*next;
	char			*line;
}	t_llist;

#endif
