/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:08 by kwang             #+#    #+#             */
/*   Updated: 2022/09/30 14:38:21 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures_mlx(void *p_mlx, t_cache *texture_cache, t_config *config)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		// cache_image(p_mlx, texture_cache + i, config->textures.textures[i]);
		++i;
	}
}
