/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:44:39 by aquinter          #+#    #+#             */
/*   Updated: 2025/02/20 20:54:12 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
	{
		print_error("Error\nUsage ./cub3D \"path_to_the_maze.cub\"\n");
		return (1);
	}
	init(argv[1]);
	return (0);
}
