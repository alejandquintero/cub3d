/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:08:28 by lgandari          #+#    #+#             */
/*   Updated: 2025/02/28 20:10:14 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_valid_id(const char *id, const char **valid_ids)
{
	int	i;

	i = 0;
	while (valid_ids[i])
	{
		if (ft_strcmp(id, valid_ids[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_texture(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

static int	count_parts(char **parts)
{
	int	count;

	count = 0;
	while (parts[count])
		count++;
	return (count);
}

// Not finished (refactor)
bool	is_valid_rgb(char *rgb_str, int *rgb)
{
	char	**parts;
	char	*trimmed;
	int		count;
	int		i;

	count = 0;
	if (!rgb_str || !*rgb_str)
		return (false);
	parts = ft_split(rgb_str, ',');
	if (!parts)
		return (false);
	if (count_parts(parts) != 3)
	{
		free_matrix(parts);
		return (false);
	}
	count = 0;
	while (count < 3)
	{
		trimmed = ft_strtrim(parts[i], " \t\n\r\v\f");
		if (!trimmed)
		{
			free_matrix(parts);
			return (false);
		}
		i = 0;
		while (trimmed[i])
		{
			if (!ft_isdigit(trimmed[i]))
			{
				free(trimmed);
				free_matrix(parts);
				return (false);
			}
			i++;
		}
		rgb[i] = ft_atoi(trimmed);
		free(trimmed);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_matrix(parts);
			return (false);
		}
		count++;
	}
	free_matrix(parts);
	return (true);
}
