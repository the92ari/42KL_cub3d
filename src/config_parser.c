/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:22 by kwang             #+#    #+#             */
/*   Updated: 2022/09/26 22:21:37 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
textures - Address of t_texture data type of populate with a string from
			configuration file.
str - single string from config cache that should represent the texture to be
		assigned and the string representation of the configuration.

Description:
Iterates through a preset list of textures that is required to be assigned to
and assigned the matched configuration to the texture. Once function call
assigns to only one texture.

Return value:
Returns nothing. Throws errors configuration is invalid.
*/
static void set_config(t_textures* textures, const char *str)
{
	char		**split;
	const char	*arr[6] = {"NO", "SO", "EA", "WE", "F", "C"};
	int			i;
	
	split = ft_split(str, ' ');
	if (ft_2darrlen(split) != 2)
		error_handler("Wrong configuration given", "set_config", EIO);
	i = -1;
	while (++i < (sizeof(arr) / sizeof(char *)))
	{
		if (ft_strcmp(split[0], arr[i]))
			textures->textures[i] = ft_strdup(split[1]);
	}
	ft_free2d(split);
}

/*
Parameters:
textures - Address of t_texture data type of populate with strings from
			configuration file.
config_cache - Value of a nested array that was populated with content from
				config file

Description:
Reads from cached configuration file and populates t_texture data structure
with strings required from image and color caching. No validation is done during
function call.

Return value:
Returns nothing. Throws errors structure fails to be completely populated.
*/
static void check_set_config(t_textures	*textures, const char **config_cache)
{
	size_t		i;

	i = 0;
	while (!is_str_map(config_cache[i]))
	{
		set_config(textures, config_cache[i]);
		i++;
	}
	if (!check_textures_set(*textures))
		error_handler("Incomplete amount of textures", "check_set_config", 0);
}

/*
Parameters:
fd - opened file descriptor belonging to the configuration file.
config_cache - address of a nested array that is populated with content from
				config file

Description:
Populates a nested array of strings obtained via get_next_line and stores them 
within config_cache for easy random access. Discards any line that only contains
whitespace characters.

Return value:
Returns nothing. Throws errors if reading or caching fails.
*/
static void	cache_config(int fd, char ***config_cache)
{
	char	*line;
	t_list	*head;
	t_list	*lst;

	head = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (errno)
			error_handler("Read error", "cache_config", 0);
		if (is_str_empty(line) == true)
		{
			free(line);
			continue;
		}
		lst = ft_lstnew(line);
		if (!lst->content)
			error_handler("Str duplicate error", "cache_config", EIO);
		ft_lstadd_back(&head, lst);
	}
	*config_cache = (char **)ft_lst_to_arr(head);
	ft_lstclear(&head, NULL);
	free(line);
}

/*
Parameters:
filename - string that represent config file in .cub extension
vars - address of custom data structure that holds essential program data

Description:
Takes a configuration file, validates its extension, validates the configuration
file contents, and assigns the essential configuration data contained in t_vars
data structure.

Return value:
Returns nothing. Throws errors if any validation fails
*/
void	parse_config(const char *filename, t_vars *vars)
{
	int			fd;
	char		**config_cache;
	t_textures	textures;

	textures = (t_textures){};
	check_ext(filename, "cub");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_handler("Failure to open file", "parse_map", 0);
	cache_config(fd, &config_cache);
	check_set_config(&textures, config_cache);
	// validate_config?
	// cache_textures(&vars->texture_cache, &config_cache);
	// cache_map(&vars->map);
	// check_map(&vars->map);
	close(fd);
}
