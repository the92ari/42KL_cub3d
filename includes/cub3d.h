#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

enum {
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	EAST_TEXTURE,
	WEST_TEXTURE,
	FLOOR,
	CEILING
};

typedef union u_textures
{
	struct s_textures
	{
		char *north;
		char *south;
		char *east;
		char *west;
		char *floor;
		char *ceiling;
	} container;
	char *textures[6];
}	t_textures;

// union colors
// {
// 	int		color;
// 	char	*rgb_string;
// };

typedef struct s_data
{
	void	*addr;
	char	*img;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_data;

typedef struct s_cache
{
	t_data	north;
	t_data	south;
	t_data	east;
	t_data	west;
	int		floor;
	int		ceiling;
}	t_cache;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	t_cache	texture_cache;
	char	**map;
}	t_vars;

// error_handler.c
void	error_handler(const char *msg, const char *func, int err_no);

// file_validator.c
void	check_valid_ext(const char *filename, const char *ext_to_check);
void	parse_config(const char *filename, t_vars *vars);

// config_parser.c
int		check_textures_set(const t_textures textures);
int		is_str_empty(const char* str);
int		is_str_map(const char *str);

// mlx_hook_functions.c
int	exit_program_mlx(t_vars* mlx)

#endif
