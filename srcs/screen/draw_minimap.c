/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/07/20 14:21:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;

void draw_tile(t_game *game, int color, int x, int y)
{
	int dx;
	int dy;
	int map_x = x * game->config.tile_size;
	int map_y = y * game->config.tile_size;

	dx = 0;
	while (dx < game->config.tile_size)
	{
		dy = 0;
		while (dy < game->config.tile_size)
		{
			if(map_x + dx >= 0 && map_x + dx < MINIMAP_WIDHT && map_y + dy >= 0 && map_y + dy < MINIMAP_HEIGHT)
			{
				if (game->map.show_minimap)
					mlx_put_pixel(game->img, map_x + dx, map_y + dy, color);
			}
			dy++;
		}
		dx++;
	}
}

void draw_borders(t_game *game)
{
	int x;
	int y;
	int color;
	t_map *map;

	x = 0;
	map = &game->map;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
				color = 0x12ADB3;
			else if (game->map.map[y][x] == '1' || game->map.map[y][x] == ' ')
				color = 0x12ADB3;
			else
				color = 0xAAAAAAFF;
			draw_tile(game, color, x, y);
			y++;
		}
		x++;
	}
}

void	draw_game(t_game *game)
{
	t_ray *rays;
	const int px = game->player.px;
	const int py = game->player.py;

	rays = (t_ray *)ft_calloc(sizeof(t_ray),  game->config.num_rays + 1);
	if (!rays)
		perror("Failed to allocate memory");
	draw_borders(game);
	calculate_raycast(game, rays, px, py);
	draw_player(game, rays, px, py);
	free(rays);
}
