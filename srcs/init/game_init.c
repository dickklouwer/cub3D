/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:32:10 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/29 15:19:24 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	st_file_check(char *file)
{
	const char	*filename;

	filename = ft_strnstr(file, ".", ft_strlen(file) + 1);
	if (!filename || ft_strncmp(filename, ".cub", ft_strlen(filename)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	config_init(t_config *config, char **argv)
{
	config->map_path = argv[1];
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->floor_color[0] = 0;
	config->floor_color[1] = 0;
	config->floor_color[2] = 0;
	config->ceiling_color[0] = 0;
	config->ceiling_color[1] = 0;
	config->ceiling_color[2] = 0;
	config->map = NULL;
	config->map_y = 0;
	config->map_x = 0;
	config->tile_size = 32;
	config->fov = 60;
	config->num_rays = 120;
	config->angle_step = (double)config->fov / (double)config->num_rays;
}

static void	map_init(t_map *map, char **argv)
{
	map->map_fd = 0;
	map->map_y = 0;
	map->map_x = 0;
	map->map_start = 0;
	map->width = 0;
	map->height = 0;
	map->path = argv[1];
}

void	init_player(t_game *game)
{
	game->player.px = (game->player.sx * game->config.tile_size) - (game->config.tile_size / 2) + (PLAYER_SIZE / 2);
	game->player.py = (game->player.sy * game->config.tile_size) - (game->config.tile_size / 2) + (PLAYER_SIZE / 2);
	if (game->player.orientation == 'N')
		game->player.pa = 270;
	else if (game->player.orientation == 'S')
		game->player.pa = 90;
	else if (game->player.orientation == 'E')
		game->player.pa = 180;
	else if (game->player.orientation == 'W')
		game->player.pa = 0;
	game->player.pdx = cos(game->player.pa / 180 * M_PI);
	game->player.pdy = sin(game->player.pa / 180 * M_PI);
}

void	game_init(t_game *game, char **argv)
{
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		perror("Failed to allocate memory..");
	if (st_file_check(argv[1]))
		err_exit("Wrong config file extension");
	map_init(&game->map, argv);
	config_init(&game->config, argv);
}
