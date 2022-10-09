/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:11:41 by kwang             #+#    #+#             */
/*   Updated: 2022/10/09 16:13:50 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cache_image(void *mlx, t_data *img, char *path)
{
	img->addr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	img->img = mlx_get_data_addr(img->addr, &img->bpp,
			&img->size_line, &img->endian);
}

static void	ceiling_drawer(t_data *bg, int colour)
{
	int	i;
	int	j;
	int	horizon;

	i = 0;
	horizon = WIN_HEIGHT / 2;
	while (i < horizon)
	{
		j = 0;
		while (j < WIN_WIDTH * 4)
		{
			bg->addr[j] = colour;
			j++;
		}
		bg->addr += bg->size_line;
		i++;
	}
}

static void	floor_drawer(t_data *bg, int colour)
{
	int	i;
	int	j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH * 4)
		{
			bg->addr[j] = colour;
			j++;
		}
		bg->addr += bg->size_line;
		i++;
	}
}

void	rectangle_drawer(t_data *data, int w, int h, int colour)
{
	int i;
	int j;
	
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < (w * 4))
		{
			data->addr[j] = colour; // need to properly assign colours by bytes
			j++;
		}
		data->addr += data->size_line;
		i++;
	}
}

void	init_bg_mlx(t_vars *vars, void *mlx, t_data *bg)
{
	bg->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	bg->addr = mlx_get_data_addr(bg->img, &bg->bpp, &bg->size_line, &bg->endian);
}

void	init_minimap_assets(void *mlx, t_cache *cache)
{
	cache->minimap_bg.img = mlx_new_image(mlx, WIN_WIDTH / 5, WIN_WIDTH / 5); // adjust the size
	cache->minimap_player.img = mlx_new_image(mlx, WIN_WIDTH / 25, WIN_WIDTH / 25); // adjust the size
	cache->minimap_obs.img = mlx_new_image(mlx, WIN_WIDTH / 25, WIN_WIDTH / 25); // adjust the size
	cache->minimap_bg.addr = mlx_get_data_addr(cache->minimap_bg.img, &cache->minimap_bg.bpp, &cache->minimap_bg.size_line, &cache->minimap_bg.endian);
	cache->minimap_player.addr = mlx_get_data_addr(cache->minimap_player.img, &cache->minimap_player.bpp, &cache->minimap_player.size_line, &cache->minimap_player.endian);
	cache->minimap_obs.addr = mlx_get_data_addr(cache->minimap_obs.img, &cache->minimap_obs.bpp, &cache->minimap_obs.size_line, &cache->minimap_obs.endian);
	rectangle_drawer(&cache->minimap_bg, WIN_WIDTH / 5, WIN_WIDTH / 5, 0); // adjust the colour
	rectangle_drawer(&cache->minimap_player, WIN_WIDTH / 25, WIN_WIDTH / 25, 0xFFFFF); // adjust the colour
	rectangle_drawer(&cache->minimap_bg, WIN_WIDTH / 25, WIN_WIDTH / 25, 0xFFFFF); // adjust the colour
}