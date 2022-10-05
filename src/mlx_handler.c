/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/10/05 21:49:46 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop(mlx.mlx);
}
