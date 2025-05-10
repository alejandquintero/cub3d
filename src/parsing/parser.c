/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:01:50 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/24 16:18:21 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*read_file(int fd)
{
	char	*line;
	char	*content;

	content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		content = ft_strjoin_free(content, line, true, true);
		if (!content)
		{
			perror("Error\nSomething was wrong in the system");
			exit(1);
		}
		line = get_next_line(fd);
	}
	return (content);
}

bool	parse_maze(char *maze_path, t_file *file, t_cub3d *cub3d)
{
	int	fd;

	if (check_extension(maze_path, ".cub") == -1)
	{
		return (print_error("Error\nInvalid file extension." \
			" It must be '.cub'\n", false), false);
	}
	fd = open(maze_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCould not open the file");
		exit(1);
	}
	file->content = read_file(fd);
	close(fd);
	if (!file->content || *file->content == '\0')
		return (print_error("Error\nNo maze to process\n", \
			false), false);
	return (extract_metadata(file, cub3d));
}

bool	store_color(t_cub3d *cub3d, const char *id, char *rgb_str)
{
	int	rgb[3];

	if (!is_valid_rgb_str(rgb_str, rgb))
		return (print_error("Error\nInvalid color.\n", false), false);
	if (ft_strcmp(id, "F") == 0)
		cub3d->floor_rgb = ft_memdup(rgb, sizeof(rgb));
	else if (ft_strcmp(id, "C") == 0)
		cub3d->ceil_rgb = ft_memdup(rgb, sizeof(rgb));
	return (true);
}
