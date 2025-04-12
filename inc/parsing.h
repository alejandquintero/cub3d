/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:34:13 by lgandari          #+#    #+#             */
/*   Updated: 2025/04/12 19:34:14 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include "structs.h"

// Parsing main
bool	parse_maze(char *maze_path, t_file *file, t_cub3d *cub3d);

// Extractors
bool	extract_metadata(t_file *file, t_cub3d *cub3d);
bool	extract_maze(t_cub3d *cub3d, char *cursor);
char	*extract_line(char **str);

// LLIST utils
t_llist	*build_ttlist(char *cursor);
bool	append_llist(t_llist **llist, char *line);
char	**llist_to_array(t_llist *llist);

// Checker utils
bool	is_valid_id(const char *id, const char **valid_ids);
bool	store_texture(t_cub3d *cub3d, const char *id, char *path);
bool	store_color(t_cub3d *cub3d, const char *id, char *rgb_str);

// Maze validation
bool	validate_maze(t_cub3d *cub3d, char **maze);
bool	is_allowed_char(char c);
bool	is_invalid_char(char c);
bool	is_player(char c);
bool	is_space(char c);
void	initialize_positions(int positions[8][2], int i, int j);

// Print utils
void	print_cub3d(const t_cub3d *cub3d);

#endif
