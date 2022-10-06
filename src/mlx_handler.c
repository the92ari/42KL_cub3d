/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/10/06 05:40:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int key, t_vars *mlx)
{
	if (key == 65307 || 53)
	{
		printf("Quitting programme\n");
		exit_program_mlx(mlx);
	}
	return (0);
}

/*
Parameters:
config - Address of config structure returned after parsing and validation

Description:
Handles all mlx relation functions.

Return value:
Returns nothing.
*/
void	handle_mlx(t_config *config)
{
	t_vars	mlx;

	mlx = (t_vars){};
	mlx.mlx = mlx_init();
	mlx.map = config->map;
	if (!mlx.mlx)
		error_handler("Display var not configured", "main", EIO);
	init_textures_mlx(mlx.mlx, &mlx.texture_cache,
		config->assets.textures, TEXTURES_SIZE);
	init_colours_mlx(&mlx.colours, config->assets.colours, COLOURS_SIZE);
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	mlx_hook(mlx.win, 17, 0, exit_program_mlx, &mlx);
	mlx_key_hook(mlx.win, key_handler, &mlx);
	mlx_loop(mlx.mlx);
}
