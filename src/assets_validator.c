/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:30:41 by kwang             #+#    #+#             */
/*   Updated: 2022/09/30 14:34:37 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
str - string representation of valid path to be checked.

Description:
Attempts to open given file path to evaluate if path is valid.

Return value:
Returns nothing. Throws error if paths fail to open.
*/
static void	validate_texture_path(const char *config_str)
{
	int	fd;

	// validate_ext(config_str, "xpm");
	fd = open(config_str, O_RDONLY);
	if (fd == -1 || errno != 0)
		error_handler("Failure to open specified path / invalid path",
			"validate_texture_path", 0);
	close(fd);
}

/*
Parameters:
str - string representation of RGB value to be checked.

Description:
Evaluates if RGB values are in valid format and range.

Return value:
Returns nothing. Throws error if rgb values are invalid.
*/
static void	validate_rgb(const char *config_str)
{
	char	**colours;
	size_t	i;
	int		val;

	i = 0;
	colours = ft_split(config_str, ',');
	while (i < 3)
	{
		if (ft_2darrlen(colours) != 3)
			error_handler("Too few RGB values", "validate_texture_rgb", EIO);
		if (is_rgb_value(colours[i]) == false)
			error_handler("Invalid RGB value", "validate_texture_rgb", EIO);
		if (ft_strlen(colours[i]) > 3)
			error_handler("RGB value greater than 255",
				"validate_texture_rgb", EIO);
		val = ft_atoi(colours[i]);
		if (val < 0 || val > 255)
			error_handler("Invalid RGB value", "validate_texture_rgb", EIO);
		++i;
	}
	ft_free2d(colours);
}

/*
Parameters:
textures - Value of t_textures struct.

Description:
Iterates through the first 4 elements of the t_texture struct to evaluate if
set paths are valid then iterates though the last 2 values to evaluate if RGB
values are valid.

Return value:
Returns nothing. Throws errors if any validation fails.
*/
void	validate_assets_config(const t_assets assets)
{
	size_t	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		validate_texture_path(assets.textures[i]);
		++i;
	}
	i = 0;
	while (i < COLOURS_SIZE)
	{
		validate_rgb(assets.colours[i]);
		++i;
	}
}