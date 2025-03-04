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

bool	is_valid_rgb_str(const char *str, int *rgb_num)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			return (false);
		rgb_num[j] = ft_atoi(&str[i]);
		if (rgb_num[j] < 0 || rgb_num[j] > 255)
			return (false);
		while (str[i] && ft_isdigit(str[i]))
			i++;
		while (str[i] && is_space(str[i]))
			i++;
		if (j < 2)
		{
			if (str[i] != ',')
				return (false);
			i++;
		}			
		j++;
	}
	while (str[i] && is_space(str[i]))
		i++;
	return (str[i] == '\0');
}
