/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:25 by kwang             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/28 16:28:23 by kwang            ###   ########.fr       */
=======
/*   Updated: 2022/09/28 16:10:28 by wwan-taj         ###   ########.fr       */
>>>>>>> da3558d96160fcf65920efb6deb7ca70b824fc3d
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_config config;

	if (argc != 2)
	{
		printf("Usage: %s [<MAP_NAME>.cub]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	parse_config(argv[1], &config);

	return (EXIT_SUCCESS);
}

// BLAHBLAH
