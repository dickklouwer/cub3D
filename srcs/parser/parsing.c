/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:56:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/23 15:56:00 by tklouwer      ########   odam.nl         */
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

int checkDuplicateTextures(t_config* config) 
{
    if(ft_strncmp(config->north_texture, config->south_texture, 100) == 0) {
        return 1;
    } 
	else if(ft_strncmp(config->north_texture, config->west_texture, 100) == 0) {
        return 1;
    } 
	else if(ft_strncmp(config->north_texture, config->east_texture, 100) == 0) {
        return 1;
    } 
	else if(ft_strncmp(config->south_texture, config->west_texture, 100) == 0) {
        return 1;
    } 
	else if(ft_strncmp(config->south_texture, config->east_texture, 100) == 0) {
        return 1;
    } 
	else if(ft_strncmp(config->west_texture, config->east_texture, 100) == 0) {
        return 1;
    } 
    return 0;
}


// int	validate_variables(t_game *game)
// {
// 	if (!game->config.east_texture
// 		|| !game->config.map || !game->config.map_path || !game->config.north_texture ||
// 		!game->config.south_texture || !game->config.west_texture)
// 		return (err_exit("cub3D: Information in Config file not parseable."));
// }

int	parse_game(t_game *game)
{
	parse_config(&game->config, game);
	parse_map(&game->map, &game->player);
	init_player(&game->player);
	flood_fill(game->player.sx, game->player.sy, &game->map, game->map.map_cpy);
	// validate_variables(game);
	return (EXIT_SUCCESS);
}
