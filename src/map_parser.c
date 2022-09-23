/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:22 by kwang             #+#    #+#             */
/*   Updated: 2022/09/23 21:57:24 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(const char *filename, t_map *map)
{
	int		fd;

	check_ext(filename, "cub");
	*map = (t_map){.board = NULL};
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_handler("Failure to open file", "parse_map", 0);
	cache_map(fd, map);
	close(fd);
	is_valid_map(map);
}
