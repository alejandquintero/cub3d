/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:57:55 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/06 23:04:24 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_invalid_char(char c)
{
	return (c == ' ' || c == '\n' || c == '\0');
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_allowed_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || is_player(c));
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
