/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:15:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/23 16:18:29 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	config_init(t_config *config, char **argv)
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

void	map_init(t_map *map, char **argv)
{
	map->map_fd = 0;
	map->map_y = 0;
	map->map_x = 0;
	map->path = argv[1];
	map->show_minimap = false;
	map->update_screen = true;
}

int	main(int argc, char **argv) 
{
	t_game	game;
	
	if (argc != 2)
		err_exit("cub3D: 2 Arguments required\n");
	game_init(&game, argv);
	parse_game(&game);
	init_screen(&game.mlx);
	draw_screen(&game);
	// temp_test_draw_walls(&game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free(game.ray);
	return (EXIT_SUCCESS);
}
