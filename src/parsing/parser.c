/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:01:50 by lgandari          #+#    #+#             */
/*   Updated: 2025/02/27 20:28:38 by aquinter         ###   ########.fr       */
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

void	parse_maze(char *maze_path, t_file *file, t_cub3d *cub3d)
{
	int	fd;

	if (!check_extension(maze_path, ".cub"))
		print_error("Error\nInvalid file extension. \
			It must be '.cub'\n", false);
	fd = open(maze_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCould not open the file");
		exit(1);
	}
	file->content = read_file(fd);
	close(fd);
	if (!file->content || *file->content == '\0')
		print_error("Error\nNo maze to process\n", false);
	else
		extract_metadata(file, cub3d);
}
