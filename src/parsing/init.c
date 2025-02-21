/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:53:06 by aquinter          #+#    #+#             */
/*   Updated: 2025/02/20 21:21:35 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	read_file(int fd)
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
	if (content)
	{
		printf("%s\n", content);
		free(content);
	}
	else
		print_error("Error\nNo maze to process\n");
}

void	init(char *file)
{
	int	fd;

	if (check_extension(file, ".cub") == true)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror("Error\nCould not open the file");
			exit(1);
		}
		read_file(fd);
		close(fd);
	}
	else
		print_error("Error\nInvalid file extension. It must be '.cub'\n");
}
