/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:16:03 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/22 16:36:40 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define GAME_WIDTH 1200
#define GAME_HEIGHT 1200
#define MINIMAP_WIDTH 1200
#define MINIMAP_HEIGHT 1200
#define PLAYER_SIZE 4
#define TILE_SIZE 32
#define RAD 0.0174533

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
	int		view_angle;		// Player view angle
	double	angle_step;
	int		player_count;
	char	orientation;
}				t_player;

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
	t_player			player;
}				t_game;

// MAIN
int		err_exit(char *str);
size_t	ft_strspn(const char *str, const char *accept);
void	prep_map_data(t_map *map, t_player *player);

// INIT
void	game_init(t_game *game, char **argv);
void	init_player(t_player *player);

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
void	temp_test_draw_walls(t_game *game);	// temp
void	draw_walls(t_game *game, float distance, double angle);

// PARSE UTILS
void	parse_color(int *color, char *line);
int		ft_isdigit_cub3d(char *str);
size_t	ft_strspn(const char *str, const char *accept);

// MINIMAP
void	draw_minimap(t_game *game);

// HOOKS
void	ft_hook(void *para);

#endif
