/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   checker.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/28 20:08:28 by lgandari		  #+#	#+#			 */
/*   Updated: 2025/02/28 20:10:14 by lgandari		 ###   ########.fr	   */
/*																			*/
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

static bool	is_valid_rgb_str(const char *str, int *rgb_num)
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

bool	store_texture(t_cub3d *cub3d, const char *id, char *path)
{
	if (check_extension(path, ".xpm42") == -1)
		return (print_error("Error\nInvalid texture extension. \
			Must be .xmp42\n", false), false);
	if (!is_valid_texture(path))
		return (print_error("Error\nInvalid texture path.\n", false), false);
	if (ft_strcmp(id, "NO") == 0)
		cub3d->north_tex = ft_strdup(path);
	else if (ft_strcmp(id, "EA") == 0)
		cub3d->east_tex = ft_strdup(path);
	else if (ft_strcmp(id, "WE") == 0)
		cub3d->west_tex = ft_strdup(path);
	else if (ft_strcmp(id, "SO") == 0)
		cub3d->south_tex = ft_strdup(path);
	return (true);
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
