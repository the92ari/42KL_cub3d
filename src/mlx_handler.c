/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/10/03 17:25:24 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mlx(t_config *config)
{
	t_vars	mlx;

	mlx = (t_vars){};
	mlx.mlx = mlx_init();
	mlx.map = config->map;
	if (!mlx.mlx)
		error_handler("Display var not configured", "main", EIO);
	// mlx_get_screen_size(mlx.mlx, &mlx.win_width, &mlx.win_height);
	// init_textures_mlx(mlx.mlx, &mlx.texture_cache, config);
	mlx.win = mlx_new_window(mlx.mlx, mlx.win_width, mlx.win_height, "Cub3d");
	mlx_hook(mlx.win, 17, 0, exit_program_mlx, &mlx);
	mlx_loop(mlx.mlx);
}
