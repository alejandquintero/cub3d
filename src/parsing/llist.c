/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:25:47 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/08 16:47:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	append_llist(t_llist **llist, char *line)
{
	t_llist	*new_llist_node;
	t_llist	*last_llist_node;

	new_llist_node = malloc(sizeof(t_llist));
	if (!new_llist_node)
		return (print_error("Error\nMemory allocation failed\n", \
			false), free_llist(*llist), false);
	new_llist_node->next = NULL;
	new_llist_node->line = line;
	if (!(*llist))
		*llist = new_llist_node;
	else
	{
		last_llist_node = *llist;
		while (last_llist_node->next)
			last_llist_node = last_llist_node->next;
		last_llist_node->next = new_llist_node;
	}
	return (true);
}

static size_t	llist_len(t_llist *llist)
{
	t_llist *current;
	int		i;

	i = 0;
	current = llist;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**llist_to_array(t_llist *llist)
{
	t_llist	*current;
	char	**strs;
	int		i;

	i = 0;
	strs = ft_calloc(sizeof(char *), llist_len(llist) + 1);
	if (!strs)
		return (print_error("Error\nMemory allocation failed\n", \
			false), NULL);
	current = llist;
	while (current != NULL)
	{
		strs[i] = ft_strdup(current->line);
		if (!strs[i])
			return (print_error("Error\nMemory allocation failed\n", \
				false), free_matrix(strs), NULL);
		i++;
		current = current->next;
	}
	return (strs);
}

char	*extract_line(char **str)
{
	char	*line;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	line = ft_substr(*str, 0, i);
	*str += i;
	if (!line)
		return (NULL);
	return (line);
}

void	free_llist(t_llist *llist)
{
	t_llist *current_next;
	t_llist *current;

	current = llist;
	while (current != NULL)
	{
		current_next = current->next;
		free(current->line);
		free(current);
		current = current_next;
	}
}
