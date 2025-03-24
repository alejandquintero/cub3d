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

static char	*extract_id(char **str)
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

static bool	process_metadata_line(char **cursor, t_file *file, t_cub3d *cub3d)
{
	char	*value;
	char	*id;
	bool	success;

	while (**cursor && (is_space(**cursor) || **cursor == '\n'))
		(*cursor)++;
	id = extract_id(cursor);
	if (!id)
		return (print_error("Error\nAn ID was expected.\n", false), false);
	if (!is_valid_id(id, file->valid_ids))
		return (print_error("Error\nInvalid ID.\n", false), free(id), false);
	while (**cursor && is_space(**cursor))
		(*cursor)++;
	value = extract_value(cursor);
	if (!value || ft_strlen(value) == 0)
		return (print_error("Error\nA value was expected for ID.\n", false), \
			free(id), free(value), false);
	success = false;
	if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "EA") == 0 || \
		ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "SO") == 0)
		success = store_texture(cub3d, id, value);
	else if (ft_strcmp(id, "F") == 0 || ft_strcmp(id, "C") == 0)
		success = store_color(cub3d, id, value);
	return (free(id), free(value), success);
}

bool	extract_maze(t_cub3d *cub3d, char *cursor)
{
	char	**maze;
	t_llist	*llist;

	while (*cursor && *cursor == '\n')
		cursor++;
	llist = build_ttlist(cursor);
	if (!llist)
		return (false);
	maze = llist_to_array(llist);
	free_llist(llist);
	if (!maze)
		return (false);
	if (!validate_maze(cub3d, maze))
		return (free_matrix(maze), false);
	if (!cub3d->dir_player)
		return (print_error("Error\nPlayer position required\n", \
			false), free_matrix(maze), false);
	cub3d->maze = maze;
	return (true);
}

bool	extract_metadata(t_file *file, t_cub3d *cub3d)
{
	char	*cursor;
	int		pairs_read;

	cursor = file->content;
	pairs_read = 0;
	while (pairs_read < 6)
	{
		if (!process_metadata_line(&cursor, file, cub3d))
			return (false);
		pairs_read++;
	}
	if (!extract_maze(cub3d, cursor))
		return (false);
	return (true);
}
