/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:16:03 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/08/11 15:06:52 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define GAME_WIDTH 1200
#define GAME_HEIGTH 1200
#define texWidth 64
#define texHeight 64
#define MINIMAP_WIDHT 1200
#define MINIMAP_HEIGHT 1200
#define PLAYER_SIZE 5
// #define TILE_SIZE 32
#define RAD 0.0174533
// #define FOV 60
// #define NUM_RAYS 120
#define MAX_RAY_LENGTH 10000
#define WALL_HEIGHT_FACTOR 1.5

# define NC			"\033[0m"
# define RED		"\033[38;5;1m"
# define GREEN		"\033[38;5;2m"
# define YELLOW		"\033[38;5;3m"
# define BLUE		"\033[38;5;4m"
# define MAGENTA	"\033[38;5;5m"
# define CYAN		"\033[38;5;6m"
# define WHITE		"\033[38;5;7m"
# define GRAY		"\033[38;5;8m"

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
	bool		show_minimap;
	bool		update_screen;
}				t_map;

typedef struct	s_player {
	int		sx;				// Start x
	int		sy;				// Start y
	double	px; 			// Player x
	double	py;				// Player y
	double	pa;				// Player angle
	double	pdx;			// Player delta x
	double	pdy;			// Player delta y
	// int		view_angle;		// Player view angle
	// double	angle_step;
	int		player_count;
	char	orientation;
}				t_player;

typedef struct	s_new_player {
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	old_dir_x;
	double	old_dir_y;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	old_plane_x;
	double	old_plane_y;
	double	time;
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wal_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		line_start_y;
	int		line_stop_y;
	int		tex_num;
	double	wall_x;
	int		tex_x;
}				t_new_player;

typedef struct	s_vars {
	int		n_text;
	int		s_text;
	int		w_text;
	int		e_text;
	int		f_color;
	int		c_color;
	int		map_found;
}				t_vars;

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

typedef struct	s_ray
{
	double	angle;
	double	dx;
	double	dy;
	double	dis_h;
	double	dis_v;
	int		px;
	int		py;
	int		rx;
	int		ry;
	int		xo;
	int		yo;
	int		mx;
	int		my;
	int		hx;
	int		hy;
	int		vx;
	int		vy;
	int		hit_h;
	int		hit_v;
	double	length;
}				t_ray;

typedef struct s_game
{
	int					map_exe;
	t_map				map;
	t_config			config;
	t_ray				*ray;
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_key_data_t		*key_data;
	t_player			player;
	t_new_player		p;
}				t_game;

// MAIN
int		err_exit(char *str);
size_t	ft_strspn(const char *str, const char *accept);
void	prep_map_data(t_map *map, t_player *player);

// INIT
void	game_init(t_game *game, char **argv);
void	init_player(t_game *game);

// PARSE CONFIG
void    parse_config(t_config *config, t_game *game);

// PARSER
int		parse_game(t_game *game);

// PARSE_MAP
void	 parse_map(t_map *map, t_player *player);

// MAP_CHECKS
int		is_map_surrounded(t_map *map);
void	map_prerequisites(t_player *player, char *line, int y);

// SCREEN
void	init_screen(mlx_t **mlx);
void	draw_screen(t_game *game);
void	update_screen(t_game *game);
void	draw_floor_and_cailing(t_game *game);
void	draw_wals(t_game *game, t_ray *ray);
// void	draw_walls(t_game *game, float distance, double angle);
// void	draw_3d_walls(mlx_image_t *image, t_ray *rays, uint32_t wall_color, uint32_t background_color);

// PARSE UTILS
void	parse_color(int *color, char *line);
int		ft_isdigit_cub3d(char *str);
size_t	ft_strspn(const char *str, const char *accept);

// MINIMAP
void	draw_game(t_game *game);

// HOOKS
void	ft_hook(void *para);
void	test_hook(void *param);

void calculate_raycast(t_game *game, t_ray *rays, int px, int py);
void draw_raycast(t_game *game, t_ray *rays);
void calculate_player(t_game *game, t_ray *rays, int px, int py);
void    draw_player(t_game *game, t_ray *rays, int px, int py);

int	check_dups(t_config *config);

void	init_test(t_game *game);
void	test(t_game *game);

#endif
