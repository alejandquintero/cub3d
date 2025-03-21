/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:06:38 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/21 18:06:41 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	close_on_esc(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = NULL;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx = (mlx_t *)param;
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
}
