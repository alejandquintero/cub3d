/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:15:36 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/08 16:44:28 by aquinter         ###   ########.fr       */
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
		if (maze[x] && maze[x][y])
		{
			if (is_invalid_char(maze[x][y]))
				return (false);
		}
		else
			return (false);
		k++;
	}
	return (true);
}

bool	handle_player(t_cub3d *cub3d, char dir)
{
	if (!cub3d->dir_player)
	{
		cub3d->dir_player = dir;
		return (true);
	}
	return (false);
}

bool	validate_maze(t_cub3d *cub3d, char **maze)
{
	int	i;
	int	j;

	i = 0;
	if (ft_arrlen((void **)maze) == 0)
		return (print_error("Error\nNonexistent maze\n", false), false);
	while (maze[i])
	{
		j = 0;
		while (maze[i][j])
		{
			if (!is_allowed_char(maze[i][j]))
				return (print_error("Error\nInvalid character in maze\n",
					false), false);
			if (!is_surrounding_valid(maze, i, j))
				return (print_error("Error\nMaze not properly enclosed\n", \
					false), false);
			if (is_player(maze[i][j]) && !handle_player(cub3d, maze[i][j]))
				return (print_error("Error\nOnly one player allowed\n", \
					false), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	extract_maze(t_cub3d *cub3d, char *cursor)
{
	char	**maze;
	char	*line;
	t_llist	*llist;

	llist = NULL;
	while (*cursor && *cursor == '\n')
		cursor++;
	while (*cursor)
	{
		line = extract_line(&cursor);
		if (!line)
			return (print_error("Error\nMemory allocation failed\n", \
				false), free_llist(llist), false);
		if (!append_llist(&llist, line))
			return (free(line), false);
		cursor++;
	}
	maze = llist_to_array(llist);
	if (!maze)
		return (free_llist(llist), false);
	if (!validate_maze(cub3d, maze))
		return (free_matrix(maze), false);
	if (!cub3d->dir_player)
		return (print_error("Error\nPlayer position required\n", \
			false), free_matrix(maze), false);
	cub3d->maze = maze;
	return (true);
}
