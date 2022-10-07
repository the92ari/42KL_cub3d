/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:08 by kwang             #+#    #+#             */
/*   Updated: 2022/10/06 18:45:46 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
p_mlx - Address of pointer returned by mlx_init()
texture_cache - Address of texture cache
textures - Array of validated paths to textures
size - size of textures array

Description:
Caches images into memory via the t_cache object.

Return value:
Returns nothing.
*/
void	init_config_textures_mlx(void *p_mlx, t_cache *texture_cache,
char *textures[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		cache_image(p_mlx, &texture_cache->textures[i], textures[i]);
		++i;
	}
}

/*
Parameters:
colour_cache - Address of colour cache
colours - array of "R,G,B" strings 
size - size of colours array

Description:
Caches images into memory via the t_cache object.

Return value:
Returns nothing.
*/
void	init_colours_mlx(t_colours *colours_cache, char *colours[], size_t size)
{
	size_t	i;
	char	**rgb_values;

	i = 0;
	while (i < size)
	{
		rgb_values = ft_split(colours[i], ',');
		colours_cache->bg.colours[i] = 0 << 24 | ft_atoi(rgb_values[0]) << 16
			| ft_atoi(rgb_values[1]) << 8
			| ft_atoi(rgb_values[2]);
		ft_free2d(rgb_values);
		++i;
	}
}
