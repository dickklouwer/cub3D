/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 11:38:15 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_player(t_game *game, int dx, int dy)
{
	int new_x;
	int new_y;
    
    new_x = game->player.sx + dx;
    new_y = game->player.sy + dy;
	if (new_x < 0 || new_y < 0 || new_x >= game->map.width || new_y >= game->map.height)
		return;
	if (game->map.map[new_y][new_x] == '1')
		return;
	game->player.sx = new_x;
	game->player.sy = new_y;
}

void	draw_player(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		while (y < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, \
				(MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2) + x, \
				(MINIMAP_HEIGTH / 2) - (PLAYER_SIZE / 2) + y, \
				0xFFFF00FF);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < 10)
	{
		mlx_put_pixel(game->img, \
			(MINIMAP_WIDTH / 2) + (x * game->player.pdx), \
			(MINIMAP_HEIGTH / 2) + (x * game->player.pdy), \
			0xFFFF00FF);
		x++;
	}
}

void	draw_tile(t_game *game, int color, int x, int y)
{
	int dx;
	int dy;
	int	map_x;
	int	map_y;

	dx = 0;
	map_x = x * 12;
	map_y = y * 12;
	while (dx < 12)
	{
		dy = 0;
		while (dy < 12)
		{
			if (dx == 0 || dy == 0 || dx == 12 - 1 || dy == 12 - 1)
				mlx_put_pixel(game->minimap, map_x + dx, map_y + dy, 0xFFFFFFFF);
			else
				mlx_put_pixel(game->minimap, map_x + dx, map_y + dy, color);
			dy++;
		}
		dx++;
	}
}
void	draw_borders(t_game *game)
{
    int		x;
	int		y;
	int		color;
	t_map	*map;

	x = 0;
	map = &game->map;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (y < 0 || y > TILE_SIZE || x < 0 || x > TILE_SIZE)
				mlx_put_pixel(game->minimap, x, y, 0x202020FF);
			else
				mlx_put_pixel(game->minimap, x, y, 0xAAAAAAFF);
			y++;
		}
		x++;
	}
}


void	draw_minimap(t_game *game)
{
	draw_borders(game);
	draw_player(game);
    
}
