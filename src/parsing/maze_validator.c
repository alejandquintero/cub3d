/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:15:36 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/03 23:44:38 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_invalid_char(char c)
{
	return (c == ' ' || c == '\n' || c == '\0');
}

void	initialize_positions(int positions[8][2], int i, int j)
{
	positions[0][0] = i - 1;
	positions[0][1] = j - 1;
	positions[1][0] = i - 1;
	positions[1][1] = j;
	positions[2][0] = i - 1;
	positions[2][1] = j + 1;
	positions[3][0] = i;
	positions[3][1] = j - 1;
	positions[4][0] = i;
	positions[4][1] = j + 1;
	positions[5][0] = i + 1;
	positions[5][1] = j - 1;
	positions[6][0] = i + 1;
	positions[6][1] = j;
	positions[7][0] = i + 1;
	positions[7][1] = j + 1;
}

bool	is_surrounding_valid(char **maze, int i, int j)
{
	int	x;
	int	y;
	int	k;
	int	positions[8][2];

	initialize_positions(positions, i, j);
	k = 0;
	while (k < 8)
	{
		x = positions[k][0];
		y = positions[k][1];
		if (maze[x] && maze[x][y])
		{
			if (is_invalid_char(maze[x][y]))
			{
				printf("Carácter inválido[%d][%d]: '%c'\n", x, y, maze[x][y]);
				return (false);
			}
		}
		else
		{
			printf("Posición inexistente[%d][%d]\n", x, y);
			return (false);
		}
		k++;
	}
	return (true);
}

bool	is_valid_maze(char *cursor)
{
	char	**maze;
	int		i;
	int		j;

	maze = ft_split(cursor, '\n');
	if (!maze)
		return (print_error("Error\nMemory allocation failed.\n", \
			false), false);
	i = 0;
	while (maze[i])
	{
		j = 0;
		while (maze[i][j])
		{
			if (maze[i][j] == '0' && !is_surrounding_valid(maze, i, j))
			{
				printf("Error\nInvalid maze!\n");
				free_matrix(maze);
				return (false);
			}
			j++;
		}
		i++;
	}
	printf("Maze valid!\n");
	free_matrix(maze);
	return (true);
}
