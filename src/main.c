/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:44:39 by aquinter          #+#    #+#             */
/*   Updated: 2025/02/28 20:27:13 by lgandari         ###   ########.fr       */
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
	init_cub3d(&cub3d);
	parse_maze(argv[1], &file, &cub3d);
	free_file(&file);
	free_cub3d(&cub3d);
	return (0);
}
