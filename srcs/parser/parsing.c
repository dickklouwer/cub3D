/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:56:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/28 11:57:09 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	flood_fill(int x, int y, t_map *map, char **map_line)
{
	if (x < 0 || y < 0 || x > map->width || y > map->height)
		return (0);
	if (map_line[y][x] == '1')
		return (0);
	if (map_line[y][x] == 'x')
		return (0);
	if (x == 0 || y == 0 || y == map->height - 1
		|| x == map->width - 1)
		return (err_exit("cub3D: Map not surrounded by walls."));
	map_line[y][x] = 'x';
	if (flood_fill(x - 1, y, map, map_line) == 1)
		return (1);
	if (flood_fill(x + 1, y, map, map_line) == 1)
		return (1);
	if (flood_fill(x, y - 1, map, map_line) == 1)
		return (1);
	if (flood_fill(x, y + 1, map, map_line) == 1)
		return (1);
	return (0);
}

int	parse_game(t_game *game)
{
	parse_config(&game->config, game);
	parse_map(&game->map, &game->player);
	init_player(game);
	flood_fill(game->player.sx, game->player.sy, &game->map, game->map.map_cpy);
	return (EXIT_SUCCESS);
}
