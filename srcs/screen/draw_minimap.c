/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/23 13:33:07 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;
#define FOV 60
#define NUM_RAYS 60
#define MAX_RAY_LENGTH 10000

void draw_tile(t_game *game, int color, int x, int y)
{
    int dx;
    int dy;
    int map_x = x * TILE_SIZE;
    int map_y = y * TILE_SIZE;

    dx = 0;
    while (dx < TILE_SIZE)
    {
        dy = 0;
        while (dy < TILE_SIZE)
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

    rays = (t_ray *)ft_calloc(sizeof(t_ray),  NUM_RAYS + 1);
	if (!rays)
		perror("Failed to allocate memory");
	draw_borders(game);
	calculate_player(game, rays, px, py);
    draw_player(game, rays, px, py);
    free(rays);
}
