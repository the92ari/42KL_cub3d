#include "cub3d.h"

/*
Parameters:
config_cache - The 2D map array stored in the stack
Description:
The continuously iterates through each line in the 2D array
and find the longest line.
Return value:
Returns the length of the longest line.
*/
static int	get_longest_line(char **config_cache)
{
	int	max;
	int	i;
	int	arrlen;

	i = 0;
	max = 0;
	arrlen = ft_2darrlen(config_cache);
	while (i < arrlen)
	{
		if (ft_strlen(config_cache[i]) > max)
			max = ft_strlen(config_cache[i]);
		i++;
	}
	return (max);
}

/*
Parameters:
map - The padded 2D array of the map
x - x coordinate of the character to be checked
y - y coordinate of the character to be checked

Description:
Recursively calls itself in 8 directions to check if each character is a
valid character.

Return value:
Returns true if valid, false otherwise.
*/
static int	check_enclosed(char **map, int x, int y)
{
	if (x < 0 || y < 0 || y > 9 || x == ft_strlen(map[y]))
		return (true);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (true);
	if (x == 0 || x == ft_strlen(map[y]) - 1
		|| y == 0 || y == ft_2darrlen(map) - 1)
		return (false);
	if (map[y][x] == ' ')
		return (false);
	map[y][x] = 'X';
	return (check_enclosed(map, x - 1, y - 1)
		&& check_enclosed(map, x + 0, y - 1)
		&& check_enclosed(map, x + 1, y - 1)
		&& check_enclosed(map, x - 1, y - 0)
		&& check_enclosed(map, x + 1, y - 0)
		&& check_enclosed(map, x - 1, y + 1)
		&& check_enclosed(map, x + 0, y + 1)
		&& check_enclosed(map, x + 1, y + 1));
}

/*
Parameters:
map - The padded 2D array of the map

Description:
Loops through `map` and executes the check_enclosed function upon finding
a '0' character

Return value:
Returns true if valid, false otherwise.
*/
static int	check_map(char **map)
{
	int	x;
	int	y;
	int	arrlen;
	int	len;

	y = 0;
	arrlen = ft_2darrlen(map);
	while (y < arrlen)
	{
		x = 0;
		len = ft_strlen(map[y]);
		while (x < len)
		{
			if (map[y][x] == '0')
			{
				if (!check_enclosed(map, x, y))
					return (false);
			}
			++x;
		}
		++y;
	}
	return (true);
}

/*
Parameters:
config_cache - Map section of the cached config.

Description:
Constructs a temporary rectangular map padded with spaces to validate.

Return value:
Returns nothing.
*/
void	validate_map(char **config_cache)
{
	char	**temp_arr;
	int		longest;

	longest = get_longest_line(config_cache);
	temp_arr = malloc(sizeof(char *) * (ft_2darrlen(config_cache) + 1));
	temp_arr[ft_2darrlen(config_cache)] = NULL;
	fill_space(temp_arr, ft_2darrlen(config_cache), longest);
	copy_into_temp(temp_arr, config_cache, longest);
	if (check_map(temp_arr) == false)
		error_handler("Invalid map structure 1", "validate_map", EIO);
	ft_free2d(temp_arr);
}
