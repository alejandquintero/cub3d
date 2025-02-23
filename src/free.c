/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/23 12:55:50 by lgandari		  #+#	#+#			 */
/*   Updated: 2025/02/23 12:55:52 by lgandari		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_file(t_file *file)
{
	if (!file)
		return ;
	if (file->content)
	{
		free(file->content);
		file->content = NULL;
	}
}
