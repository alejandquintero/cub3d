/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:15:36 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/29 13:05:09 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_surrounding_valid(char **maze, int i, int j)
{
	int	x;
	int	y;
	int	k;
	int	positions[8][2];

	if (maze[i][j] != '0' && !is_player(maze[i][j]))
		return (true);
	initialize_positions(positions, i, j);
	k = 0;
	while (k < 8)
	{
		x = positions[k][0];
		y = positions[k][1];
		if (x < 0 || maze[x] == NULL)
			return (false);
		if (y < 0 || y > (int)ft_strlen(maze[x]))
			return (false);
		if (is_invalid_char(maze[x][y]))
			return (false);
		k++;
	}
	return (true);
}

bool	handle_player(t_cub3d *cub3d, char **maze, int i, int j)
{
	if (!cub3d->dir_player)
	{
		cub3d->dir_player = maze[i][j];
		cub3d->pos_player_x = j;
		cub3d->pos_player_y = i;
		return (true);
	}
	return (false);
}

bool	are_maze_chars_valid(char **maze)
{
	int	i;
	int	j;

	i = 0;
	while (maze[i])
	{
		j = 0;
		while (maze[i][j])
		{
			if (!is_allowed_char(maze[i][j]))
				return (print_error("Error\nInvalid character in maze\n", \
					false), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_maze(t_cub3d *cub3d, char **maze)
{
	int	i;
	int	j;

	i = 0;
	if (!are_maze_chars_valid(maze))
		return (false);
	while (maze[i])
	{
		j = 0;
		while (maze[i][j])
		{
			if (!is_surrounding_valid(maze, i, j))
				return (print_error("Error\nMaze not properly enclosed\n", \
					false), false);
			if (is_player(maze[i][j]) && !handle_player(cub3d, maze, i, j))
				return (print_error("Error\nOnly one player allowed\n", \
					false), false);
			j++;
		}
		i++;
	}
	return (true);
}

char	*extract_line(char **str)
{
	char	*line;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	line = ft_substr(*str, 0, i);
	*str += i;
	if (!line)
		return (print_error("Error\nMemory allocation failed\n", \
			false), NULL);
	return (line);
}
