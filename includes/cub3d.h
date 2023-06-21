/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:16:03 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/21 13:01:13 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define GAME_WIDTH 1200
#define GAME_HEIGTH 1200

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
	char	*path;
	char	**map;
	char	**map_cpy;
	int		map_fd;
	int		map_y;
	int		map_x;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	bool	show_minimap;
}					t_map;

typedef struct	s_player {
	int		start_x;
	int		start_y;
	int		pos_x;
	int		pos_y;
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

// MINIMAP
void	draw_2d_map(t_game *game);

// HOOKS
void	ft_hook(void *para);

#endif
