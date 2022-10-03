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

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

enum e_textures{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	TEXTURES_SIZE
};

enum e_colours{
	FLOOR,
	CEILING,
	COLOURS_SIZE
};

typedef struct s_assets
{
	char	*textures[TEXTURES_SIZE];
	char	*colours[COLOURS_SIZE];
}	t_assets;

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
}	t_cache;

typedef struct s_colours
{
	int		floor;
	int		ceiling;
}	t_colours;

typedef struct s_config
{
	t_assets	textures;
	char		**map;
}	t_config;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_cache		texture_cache;
	t_colours	colours;
	char		**map;
}	t_vars;

// error_handler.c
void	error_handler(const char *msg, const char *func, int err_no);

// file_validator.c
void	validate_ext(const char *filename, const char *ext_to_check);

// config_parser.c
void	parse_config(const char *filename, t_config *config);

// assets_validator.c
void	validate_assets_config(const t_assets assets);

// config_parser_helper.c
int		check_assets_set(const t_assets assets);

// config_parsing_utils.c
int		is_str_empty(const char *str);
int		is_str_map(const char *str);
int		is_rgb_value(const char *str);

// map_validator_utils.c
void	fill_space(char **temp_arr, int arrlen, int size);
void	copy_into_temp(char **dst, char **src, int len);

// map_validator.c
void	validate_map(char **config_cache);

// mlx_handler.c
void	handle_mlx(t_config *config);

// mlx_hook_functions.c
int		exit_program_mlx(t_vars *mlx);

// image_utils.c
void	cache_image(void *mlx, t_data *img, char *path);

#endif
