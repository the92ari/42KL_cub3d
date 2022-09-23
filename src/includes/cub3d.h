#ifndef CUB3D_H
# define CUB3D_H

// error_handler.c
void	error_handler(const char *msg, const char *func, int err_no);

// file_validator.c
void	check_valid_ext(const char *filename, const char *ext_to_check);
// void	parse_map(char *filename, t_map *map);

#endif
