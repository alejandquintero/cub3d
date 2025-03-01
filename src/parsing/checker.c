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
