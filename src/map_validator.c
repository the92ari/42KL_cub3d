#include "cub3d.h"

/*
Parameters:
c - the character that is to be checked. The character is a character
that is adjacent to a space character in the map

Description:
This is just an extension to check_surrounding_elem (to overcome norminette rules).
This function will check whether c is either a 1 or a space as only these two characters
are valid to be around another space character in the map.

Return value:
Return 1 if the parameter is not a valid character. 0 otherwise
*/
static int check_elem(char c)
{
	if (c != ' ' && c != '1')
		return (1);
	return (0);
}

/*
Parameters:
config_cache - the temporary 2D array that stores the lines from .cub.
i - the string index
j - the character index

Description:
Will loop through the elements surrounding the element at index i and j

Return value:
Return false if it encounters an invalid character surrounding the element to be checked
*/
// source: https://stackoverflow.com/questions/652106/finding-neighbours-in-a-two-dimensional-array
// still might need to do boundary checking
int check_surrounding_elem(char **config_cache, int i, int j)
{
	int	row_limit;
	int col_limit;
	int	x;
	int y;

	row_limit = ft_2darrlen(config_cache);
	if (row_limit > 0)
	{
		col_limit = ft_strlen(config_cache[i]);
		x = ft_max(0, i - 1);
		while (x <= ft_min(i + 1, row_limit))
		{
			y = ft_max(0, j - 1);
			while (y <= ft_min(j + 1, col_limit))
			{
				if ((x != i || y != j) && check_elem(config_cache[x][y]))
					return (0);
				y++;
			}
			x++;
		}
	}
	return (1);
}

/*
Parameter:
config_cache - a temporrary 2D array that stores all the lines
from the .cub file. The parameter is passed while the pointer is already being pointed
at the line where the map starts. This is done from the function caller side.

Description:
It will scan through each character elements in the map and upon encountering a space
character, it will call the check_surrounding_elem that will check the characters
surrounding the space.

Return value:
Returns false if check_surrounding_elem encounters an error. Else, returns true.
*/
int	check_space_validity(char **config_cache)
{
	int i;
	int j;

	i = 0;
	while (i < ft_2darrlen(config_cache))
	{
		j = 0;
		while (j < ft_strlen(config_cache[i]))
		{
			if (config_cache[i][j] == ' ')
			{
				if (check_surrounding_elem(config_cache, i, j) == 0) // can combine this if check with the previous if check using &&
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	validate_map(char **config_cache)
{
	if (check_space_validity(config_cache) == 0)
		error_handler("Invalid map structure", "validate_map", EIO);
}