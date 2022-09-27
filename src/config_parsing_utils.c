#include "cub3d.h"

/*
Parameters:
textures - data structure to be checked if data members are unpopulated.

Description:
Iterates through t_textures data structure and evaluate is any variable is set
to NULL; 

Return value:
Returns true if all variables have a non-NULL value; false otherwise.
*/
int check_textures_set(const t_textures textures)
{
	size_t	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		if (textures.textures[i] == NULL)
			return (false);
		++i;
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for non-whitespace characters i.e. \t,\v,\n,\r,' '
to identify if the current line is empty.

Return value:
Returns true if all characters are whitespace characters; false if not.
*/
int	is_str_empty(const char* str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (false);
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for characters only available to map. i.e.
1, 0, N, S, E, W. to identify if the current line belongs to a map element.

Return value:
Returns true if all characters are characters available to map; false otherwise
*/
int is_str_map(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_strchr(" \t\r\n\v01NSWE", str[i]) == NULL)
			return (false);
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for only digit characters in the string.

Return value:
Returns true if all characters are digits; false otherwise
*/
int	is_rgb_value(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}
