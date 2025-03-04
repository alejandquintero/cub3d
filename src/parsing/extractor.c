/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   extractor.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aquinter <aquinter@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/27 20:27:07 by aquinter		  #+#	#+#			 */
/*   Updated: 2025/03/03 23:43:03 by aquinter		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*extract_id(char **str)
{
	char	*id;
	int		i;

	i = 0;
	while (**str && is_space(**str))
		(*str)++;
	while ((*str)[i] && !is_space((*str)[i]))
		i++;
	id = ft_substr(*str, 0, i);
	*str += i;
	if (!id || ft_strlen(id) == 0)
	{
		free(id);
		return (NULL);
	}
	return (id);
}

static char	*extract_value(char **str)
{
	char	*value;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	value = ft_substr(*str, 0, i);
	*str += i;
	if (**str == '\n')
		(*str)++;
	return (value);
}

static void print_cub3d(t_cub3d *cub3d)
{
	printf("\n--- STORED DATA IN t_cub3d ---\n");
	printf("North Texture: %s\n", cub3d->north_tex ? cub3d->north_tex : "NULL");
	printf("South Texture: %s\n", cub3d->south_tex ? cub3d->south_tex : "NULL");
	printf("West Texture: %s\n", cub3d->west_tex ? cub3d->west_tex : "NULL");
	printf("East Texture: %s\n", cub3d->east_tex ? cub3d->east_tex : "NULL");
	if (cub3d->floor_rgb)
		printf("Floor Color: [%d, %d, %d]\n", cub3d->floor_rgb[0], cub3d->floor_rgb[1], cub3d->floor_rgb[2]);
	else
		printf("Floor Color: NULL\n");
	if (cub3d->ceil_rgb)
		printf("Ceiling Color: [%d, %d, %d]\n", cub3d->ceil_rgb[0], cub3d->ceil_rgb[1], cub3d->ceil_rgb[2]);
	else
		printf("Ceiling Color: NULL\n");
	printf("--- END OF STRUCT DATA ---\n");
}

bool	extract_metadata(t_file *file, t_cub3d *cub3d)
{
	char	*cursor;
	char	*value;
	char	*id;
	int		pairs_read;
	int		rgb[3];

	cursor = file->content;
	pairs_read = 0;
	printf("Content before processing file:\n%s\n", file->content);
	printf("Content after processing file\n");
	while (pairs_read < 6)
	{
		while (*cursor && (is_space(*cursor) || *cursor == '\n'))
			cursor++;
		id = extract_id(&cursor);
		if (!id)
			return (print_error("Error\nAn ID was expected.\n", false), false);
		if (!is_valid_id(id, file->valid_ids))
			return (print_error("Error\nInvalid ID.\n", false), free(id), false);
		while (*cursor && is_space(*cursor))
			cursor++;
		value = extract_value(&cursor);
		if (!value || ft_strlen(value) == 0)
			return (print_error("Error\nA value was expected for ID.\n", false), free(id), free(value), false);
		if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "EA") == 0 || \
			ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "SO") == 0)
		{
			if (!is_valid_texture(value))
			{
				free(id);
				free(value);
				return (print_error("Error\nInvalid texture path.\n", false), false);
			}
			if (ft_strcmp(id, "NO") == 0)
				cub3d->north_tex = ft_memdup(value, ft_strlen(value) + 1);
			else if (ft_strcmp(id, "EA") == 0)
				cub3d->east_tex = ft_memdup(value, ft_strlen(value) + 1);
			else if (ft_strcmp(id, "WE") == 0)
				cub3d->west_tex = ft_memdup(value, ft_strlen(value) + 1);
			else if (ft_strcmp(id, "SO") == 0)
				cub3d->south_tex = ft_memdup(value, ft_strlen(value) + 1);
		}
		else if (ft_strcmp(id, "F") == 0 || ft_strcmp(id, "C") == 0)
		{
			if (!is_valid_rgb_str(value, rgb))
			{
				free(id);
				free(value);
				return (print_error("Error\nInvalid color value.\n", false), false);
			}
			if (ft_strcmp(id, "F") == 0)
				cub3d->floor_rgb = ft_memdup(rgb, sizeof(rgb));
			else if (ft_strcmp(id, "C") == 0)
				cub3d->ceil_rgb = ft_memdup(rgb, sizeof(rgb));
		}
		printf("ID = [%s]; VALUE = [%s]\n", id, value);
		free(id);
		free(value);
		pairs_read++;
	}
	is_valid_maze(cursor);
	print_cub3d(cub3d);
	return (true);
}
