/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:45:21 by lgandari          #+#    #+#             */
/*   Updated: 2025/05/10 09:45:23 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	is_valid_texture(const char *path)
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
		if (j < 2 && str[i++] != ',')
			return (false);
		j++;
	}
	while (str[i] && is_space(str[i]))
		i++;
	return (str[i] == '\0');
}

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

static bool	assign_texture(char **dest, const char *id, const char *path)
{
	if (*dest != NULL)
	{
		print_error("Error\nDuplicate texture ID: ", false);
		write(2, id, ft_strlen(id));
		write(2, "\n", 1);
		return (false);
	}
	*dest = ft_strdup(path);
	return (true);
}

bool	store_texture(t_cub3d *cub3d, const char *id, char *path)
{
	if (check_extension(path, ".xpm42") == -1)
		return (print_error("Error\nInvalid texture extension. \
			Must be .xmp42\n", false), false);
	if (!is_valid_texture(path))
		return (print_error("Error\nInvalid texture path.\n", false), false);
	if (ft_strcmp(id, "NO") == 0)
		return (assign_texture(&cub3d->north_tex, id, path));
	else if (ft_strcmp(id, "EA") == 0)
		return (assign_texture(&cub3d->east_tex, id, path));
	else if (ft_strcmp(id, "WE") == 0)
		return (assign_texture(&cub3d->west_tex, id, path));
	else if (ft_strcmp(id, "SO") == 0)
		return (assign_texture(&cub3d->south_tex, id, path));
	return (false);
}
