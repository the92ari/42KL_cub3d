/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:30 by kwang             #+#    #+#             */
/*   Updated: 2022/09/23 21:57:33 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_handler(const char *msg, const char *func_name, int err_no)
{
	if (err_no)
		errno = err_no;
	printf("Error\n");
	printf("%s\n", msg);
	perror(func_name);
	exit(EXIT_FAILURE);
}
