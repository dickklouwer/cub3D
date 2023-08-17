/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:32:10 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/08/17 19:36:23 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int st_file_check(char *file)
{
	char *filename;

	filename = ft_strnstr(file, ".", ft_strlen(file) + 1);
	if (!filename || ft_strncmp(filename, ".cub", 4) || ft_strlen(filename) != 4)
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
	config->floor_color[0] = -1;
	config->floor_color[1] = -1;
	config->floor_color[2] = -1;
	config->ceiling_color[0] = -1;
	config->ceiling_color[1] = -1;
	config->ceiling_color[2] = -1;
	config->map = NULL;
	config->map_y = 0;
	config->map_x = 0;
	config->tile_size = 32;
	config->fov = 60;
	config->num_rays = config->fov * 2;
	config->angle_step = (double)config->fov / (double)config->num_rays;
	config->move_speed = 1;
	config->rotate_speed = 3;
}

static void	map_init(t_map *map, char **argv)
{
	map->path = argv[1];
	map->map_fd = 0;
	map->map_start = 0;
	map->map_x = 0;
	map->map_y = 0;
	map->width = 0;
	map->height = 0;
	map->update_screen = true;
}

void	game_init(t_game *game, int	argc, char **argv)
{
	if (argc != 2)
		err_exit("cub3D: 2 Arguments required\n");
	if (st_file_check(argv[1]))
		err_exit("Wrong config file extension");
	map_init(&game->map, argv);
	config_init(&game->config, argv);
}
