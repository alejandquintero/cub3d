/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:44:39 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_file	file;
	t_cub3d	cub3d;

	file.content = NULL;
	if (argc != 2 || !argv[1][0])
		print_error("Error\nUsage ./cub3D \"path_to_the_maze.cub\"\n", true);
	init_structs(&cub3d, &file);
	if (parse_maze(argv[1], &file, &cub3d))
		open_window(&cub3d);
	free_structs(&cub3d, &file);
	return (0);
}
