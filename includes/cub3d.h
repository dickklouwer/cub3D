/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:16:03 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/08/17 20:00:37 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define GAME_WIDHT 1600
#define GAME_HEIGHT 1200

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line.h"

typedef struct	s_map {
	char		*path;
	char		**map;
	char		**map_cpy;
	int			width;
	int			height;
	int			map_start;
	int			map_fd;
	int			map_y;
	int			map_x;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	bool		update_screen;
}				t_map;

typedef struct	s_new_player {
	int				player_count;
	int				start_x;
	int				start_y;
	double			pos_x;
	double			pos_y;
	int				map_x;
	int				map_y;
	char			orientation;
	int				pitch;
	double			dir_x;
	double			old_dir_x;
	double			old_dir_y;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			old_plane_x;
	double			old_plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wal_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				line_start_y;
	int				line_stop_y;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	mlx_texture_t	*texture;
	mlx_texture_t	*texture_n;
	mlx_texture_t	*texture_e;
	mlx_texture_t	*texture_s;
	mlx_texture_t	*texture_w;
	int				color;
}				t_new_player;

typedef struct	s_config {
	char	*map_path;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_y;
	int		map_x;
	int		tile_size;
	int		fov;
	int		num_rays;
	double	angle_step;
	double	move_speed;
	double	rotate_speed;
}				t_config;

typedef struct s_game
{
	int					map_exe;
	t_map				map;
	t_config			config;
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_key_data_t		*key_data;
	t_new_player		p;
}				t_game;

// MAIN
int		err_exit(char *str);
size_t	ft_strspn(const char *str, const char *accept);
void	prep_map_data(t_game *game);

// INIT
void	game_init(t_game *game, int	argc, char **argv);

// PARSE CONFIG
void    parse_config(t_config *config, t_game *game);

// PARSER
int		parse_game(t_game *game);

// PARSE_MAP
void	 parse_map(t_map *map);

// MAP_CHECKS
void	map_prerequisites(t_game *game, char *line, int y);

// SCREEN
void	init_screen(mlx_t **mlx);
void	draw_screen(t_game *game);
void	update_screen(t_game *game);
void	draw_floor_and_cailing(t_game *game);

// PARSE UTILS
void	parse_color(int *color, char *line);
int		ft_isdigit_cub3d(char *str);
size_t	ft_strspn(const char *str, const char *accept);

// MINIMAP

// HOOKS
void	test_hook(void *param);

int		check_dups(t_config *config);

void	init_test(t_game *game);
void	test(t_game *game);

#endif
