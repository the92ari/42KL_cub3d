#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "../libft/libft.h"

# define TEXTURES_SIZE sizeof(t_textures)/sizeof(char *)

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

typedef struct s_config
{
	t_textures	textures_config;
	char		**map;
}	t_config;

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
void	validate_ext(const char *filename, const char *ext_to_check);

// config_parser.c
void	parse_config(const char *filename, t_config *config);

// config_validator.c
void	validate_texture_config(t_textures textures);

// config_parsing_utils.c
int		check_textures_set(const t_textures textures);
int		is_str_empty(const char* str);
int		is_str_map(const char *str);
int		is_rgb_value(const char *str);

#endif
