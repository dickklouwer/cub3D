/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:32:10 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/08 14:30:32 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	game_init(t_game *game, char **argv)
{
	if (st_file_check(argv[1]))
		err_exit("Wrong config file extension");
	map_init(&game->map, argv);
	config_init(&game->config, argv);
}
