/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:15:36 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/20 22:35:16 by aquinter         ###   ########.fr       */
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

bool	handle_player(t_cub3d *cub3d, char **maze, int i, int j)
{
	if (!cub3d->dir_player)
	{
		cub3d->dir_player = maze[i][j];
		cub3d->dir_player_x = j;
		cub3d->dir_player_y = i;
		return (true);
	}
	return (false);
}

bool	validate_maze(t_cub3d *cub3d, char **maze)
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

t_llist	*build_ttlist(char *cursor)
{
	t_llist	*llist;
	char	*line;

	llist = NULL;
	while (*cursor)
	{
		line = extract_line(&cursor);
		if (!line)
			return (free_llist(llist), NULL);
		if (!append_llist(&llist, line))
			return (free(line), NULL);
		cursor++;
	}
	if (!llist)
		return (print_error("Error\nNonexistent maze\n", \
			false), NULL);
	return (llist);
}

bool	extract_maze(t_cub3d *cub3d, char *cursor)
{
	char	**maze;
	t_llist	*llist;

	while (*cursor && *cursor == '\n')
		cursor++;
	llist = build_ttlist(cursor);
	if (!llist)
		return (false);
	maze = llist_to_array(llist);
	free_llist(llist);
	if (!maze)
		return (false);
	if (!validate_maze(cub3d, maze))
		return (free_matrix(maze), false);
	if (!cub3d->dir_player)
		return (print_error("Error\nPlayer position required\n", \
			false), free_matrix(maze), false);
	cub3d->maze = maze;
	return (true);
}
