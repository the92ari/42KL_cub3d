#include "cub3d.h"

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
void	fill_space(char **temp_arr, int arrlen, int size)
{
	int	i;

	i = 0;
	while (i < arrlen)
	{
		temp_arr[i] = malloc(sizeof(char) * (size + 1));
		temp_arr[i][size] = '\0';
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
void	copy_into_temp(char **dst, char **src, int len)
{
	size_t	i;
	size_t	j;
	int		arrlen;

	arrlen = ft_2darrlen(src);
	i = 0;
	while (i < arrlen)
	{
		ft_memcpy(dst[i], src[i], len);
		i++;
	}
}
