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
	if (c != ' ' && c != '1' && c != '\n')
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
Returns 0 if it encounters an invalid character surrounding the element to be checked.
Returns 1 otherwise.
*/
// source: https://stackoverflow.com/questions/652106/finding-neighbours-in-a-two-dimensional-array
// still might need to do boundary checking
// POSSIBLE BUG: I THINK CHARACTERS ON THE LAST LINE MIGHT BE TRYING TO ACCESS ELEMENT IN THE NULL POINTER TERMINATOR
int check_surrounding_elem(char **config_cache, int i, int j)
{
	int	row_limit;
	int col_limit;
	int	x;
	int y;

	// printf("central element: %d\ni: %d j: %d\n", config_cache[i][j], i , j);
	row_limit = ft_2darrlen(config_cache);
	if (row_limit > 0)
	{
		col_limit = ft_strlen(config_cache[i]);
		x = ft_max(0, i - 1);
		while (x < ft_min(i + 1, row_limit))
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
	int	arrlen;

	i = 0;
	arrlen = ft_2darrlen(config_cache);
	while (i < arrlen)
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

int		get_longest_line(char **config_cache)
{
	int	max;
	int	i;

	i = 0;
	max = 0;
	while (i < ft_2darrlen(config_cache))
	{
		if (ft_strlen(config_cache[i]) > max)
			max = ft_strlen(config_cache[i]);
		i++;
	}
	return (max);
}

static void	fill_space(char **temp_arr, int arrlen, int size)
{
	int i;

	i = 0;
	while (i < arrlen)
	{
		temp_arr[i] = malloc(sizeof(char) * size + 2);
		temp_arr[i][size] = '\n';
		temp_arr[i][size + 1] = '\0';
		ft_memset(temp_arr[i], ' ', size);
		i++;
	}
}

static void	copy_characters(char *dst, const char *src)
{
	size_t i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
}

static void copy_into_temp(char **dst, char **src)
{
	int i = 0;

	while (i < ft_2darrlen(src))
	{
		copy_characters(dst[i], src[i]);
		i++;
	}
}

static int	chk_top_and_bot(char **temp_arr, int arrlen)
{
	size_t	i;

	i = 0;
	while (temp_arr[0][i] != '\n' && temp_arr[0][i] != '\0')
	{
		if (temp_arr[0][i] != ' ' && temp_arr[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (temp_arr[arrlen - 1][i] != '\n' && temp_arr[arrlen - 1][i] != '\0')
	{
		if (temp_arr[arrlen - 1][i] != ' ' && temp_arr[arrlen - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	chk_left_and_right(char **temp_arr, int longest)
{
	size_t	i;

	i = 0;
	while (temp_arr[i] != NULL)
	{
		if (temp_arr[i][0] != ' ' && temp_arr[i][0] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (temp_arr[i] != NULL)
	{
		if (temp_arr[i][longest - 1] != ' ' && temp_arr[i][longest - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static	void print_2d(char **array)
{
	for (int i = 0; i < ft_2darrlen(array); i++)
		printf("%s", array[i]);
}

int		check_enclosed(char **temp_arr, int longest)
{
	if (chk_top_and_bot(temp_arr, ft_2darrlen(temp_arr)) == 0)
		return (0);
	if (chk_left_and_right(temp_arr, longest) == 0)
		return (0);
	return (1);
}

void	validate_map(char **config_cache)
{
	char	**temp_arr;
	int		longest;

	longest = get_longest_line(config_cache);
	temp_arr = malloc(sizeof(char *) * ft_2darrlen(config_cache) + 1);
	temp_arr[ft_2darrlen(config_cache)] = NULL;
	fill_space(temp_arr, ft_2darrlen(config_cache), longest);
	copy_into_temp(temp_arr, config_cache);
	if (check_enclosed(temp_arr, longest) == 0)
		error_handler("Invalid map structure 1", "validate_map", EIO);
	if (check_space_validity(temp_arr) == 0)
		error_handler("Invalid map structure", "validate_map", EIO);
	ft_free2d(temp_arr);
}