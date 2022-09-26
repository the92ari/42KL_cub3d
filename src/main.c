/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:25 by kwang             #+#    #+#             */
/*   Updated: 2022/09/26 17:40:38 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv){

	t_vars	vars;
	
	if (argc == 2)
	{
		parse_config(argv[1], &vars);
	}
	else
		printf("Usage: %s [<MAP_NAME>.cub]\n", argv[0]);

	return 0;
}
