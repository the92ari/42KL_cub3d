/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:08 by kwang             #+#    #+#             */
/*   Updated: 2022/10/05 21:02:48 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
p_mlx - Address of pointer returned by mlx_init()
texture_cache - Address of texture cache
config - Address of config structure returned after parsing and validation

Description:
Caches images into memory via the t_cache object.

Return value:
Returns nothing.
*/
void	init_textures_mlx(void *p_mlx, t_cache *texture_cache, char *textures[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		cache_image(p_mlx, &texture_cache->textures[i], textures[i]);
		++i;
	}
}
