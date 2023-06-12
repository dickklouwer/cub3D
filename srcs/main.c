/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:15:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/12 13:08:47 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err_exit(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t count = 0;

	while (*str && ft_strchr(accept, *str))
	{
		count++;
		str++;
	}
	return count;
}

/* 
**	STRNSTR takes the extension and compares the values to a ".ber" file.
*/
int	st_file_check(char *file)
{
	const char	*filename;

	filename = ft_strnstr(file, ".", ft_strlen(file) + 1);
	if (!filename || ft_strncmp(filename, ".cub", ft_strlen(filename)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
}
void	game_init(t_game *game, char **argv)
{
	if (st_file_check(argv[1]))
		err_exit("Wrong config file extension");
	map_init(&game->map, argv);
	config_init(&game->config, argv);
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
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
