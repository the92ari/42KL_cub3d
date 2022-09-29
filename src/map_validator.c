#include "cub3d.h"

/*
Just temporary function to be used for debugging purposes. Prints the 2D array
without newlines
*/
static	void print_2d(char **array)
{
	for (int i = 0; i < ft_2darrlen(array); i++)
		printf("%s", array[i]);
}

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

/*
Parameters:
config_cache - The 2D map array stored in the stack

Description:
The continuously iterates through each line in the 2D array
and find the longest line.

Return value:
Returns the length of the longest line.
*/
static int		get_longest_line(char **config_cache)
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
temp_arr - An empty 2D array
arrlen - The length of temp_arr
size - Size of the array that is going to be filled up with spaces

Description:
This function will take in an empty 2D array and memory allocate
each character pointer by the size of 'size + 2'. It will be terminated
with a newline character followed by nul terminator.
The remaining bytes will be filled with the space character

Return value:
Does not return anything
*/
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

/*
Parameters:
dst - The destination 2D array
src - The source 2D array

Description:
It will copy all characters from src into dst string by string.
It will not nul terminate the string afterit finishes copying.

Return value:
Does not return anything
*/
static void copy_into_temp(char **dst, char **src)
{
	size_t	i;
	size_t	j;
	int		arrlen;

	arrlen = ft_2darrlen(src);
	i = 0;
	while (i < arrlen)
	{
		j = 0;
		while (src[i][j] != '\0')
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

/*
Parameters:
temp_arr - The temporary array that has the copy of the map padded with spaces
arrlen - the length of temp_arr

Description:
It will check the topmost and bottommost row for invalid characters.
Invalid characters are anything aside from '1' and ' '

Return value:
Returns 0 if it encounters an invalid character. Returns 1 otherwise.
*/
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

/*
Parameters:
temp_arr - The temporary array that has the copy of the map padded with spaces
longest - the length of each string

Description:
It will check the leftmost and rightmost column for invalid characters.
Invalid characters are anything aside from '1' and ' '

Return value:
Returns 0 if it encounters an invalid character. Returns 1 otherwise.
*/
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


/*
Parameters:
temp_arr - the malloc 2D array that was copied from config_cache
longest - the longest string in the 2D array.

Description:
It will call two functions to check for invalid characters.
First function is to check the top and bottom border.
Second function is to check the left-most and right-most border.

Return values:
Returns 0 if an invalid character is found. Returns 1 otherwise.
*/
int		check_enclosed(char **temp_arr, int longest)
{
	if (chk_top_and_bot(temp_arr, ft_2darrlen(temp_arr)) == 0)
		return (0);
	if (chk_left_and_right(temp_arr, longest) == 0)
		return (0);
	return (1);
}


/*
Parameters:
config_cache - The 2D configuration array stored in the stack

Description:
The function will duplicate the map in a 2D array that is padded with spaces.
It will check for any invalid characters along the rectangular border.
It will then also check if there's any space character that is not at the edges
and will check the surround 8 elements for any invalid characters.

Return value:
Does not return anything
*/
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