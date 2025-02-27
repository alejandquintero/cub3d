/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:27:07 by aquinter          #+#    #+#             */
/*   Updated: 2025/02/27 20:28:27 by aquinter         ###   ########.fr       */
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

bool	extract_metadata(t_file *file)
{
	char	*str;
	char	*id;
	char	*id2;
	char	*id3;

	str = file->content;
	id = extract_id(&str);
	if (!id)
	{
		printf("Error\nAn ID was expected.\n");
		return (false);
	}
	printf("ID: [%s]\n", id);
	free(id);
	id2 = extract_id(&str);
	if (!id2)
	{
		printf("Error\nAn ID was expected.\n");
		return (false);
	}
	printf("ID2: [%s]\n", id2);
	free(id2);
	id3 = extract_id(&str);
	if (!id3)
	{
		printf("Error\nAn ID was expected.\n");
		return (false);
	}
	printf("ID3: [%s]\n", id3);
	free(id3);
	return (true);
}
