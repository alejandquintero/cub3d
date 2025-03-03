/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:27:07 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/03 23:43:03 by aquinter         ###   ########.fr       */
/*                                                                            */
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

bool	extract_metadata(t_file *file, t_cub3d *cub3d)
{
	char	*cursor;
	int		pairs_read;
	char	*id;
	char	*value;

	(void)cub3d;
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
		{
			print_error("Error\nAn ID was expected.\n", false);
			return (false);
		}
		if (!is_valid_id(id, file->valid_ids))
		{
			print_error("Error\nInvalid ID.\n", false);
			free(id);
			return (false);
		}
		while (*cursor && is_space(*cursor))
			cursor++;
		value = extract_value(&cursor);
		if (!value || ft_strlen(value) == 0)
		{
			print_error("Error\nA value was expected for ID.\n", false);
			free(id);
			free(value);
			return (false);
		}
		printf("ID = [%s]; VALUE = [%s]\n", id, value);
		free(id);
		free(value);
		pairs_read++;
	}
	is_valid_maze(cursor);
	return (true);
}
