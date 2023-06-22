/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 16:43:36 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;
#define FOV 60
#define NUM_RAYS 30
#define MAX_RAY_LENGTH 10000

void    raycasting(t_game *game, int px, int py)
{
    int ray;
    int ray_px;
    int ray_py;
    int ray_length;

    ray = -NUM_RAYS / 2;
    while (ray <= NUM_RAYS/2) 
    {
        double ray_angle = (game->player.pa + ray * FOV / NUM_RAYS) * (M_PI/180);
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        ray_length = 0;
        while (ray_length < MAX_RAY_LENGTH)
        {
            ray_px = px + ray_length * ray_dx;
            ray_py = py + ray_length * ray_dy;
            mlx_put_pixel(game->img, ray_px, ray_py, 0xFFFF00FF);
            if (game->map.map[ray_py / TILE_SIZE][ray_px / TILE_SIZE] == '1')
            {
                break;
            }
            ray_length++;
        }
        ray++;
    }
}
void draw_player(t_game *game)
{
    int x;
    int y;
    int px = game->player.px;
    int py = game->player.py;

    x = 0;
    while (x < PLAYER_SIZE)
    {
        y = 0;
        while (y < PLAYER_SIZE)
        {
            mlx_put_pixel(game->img, px + x - PLAYER_SIZE / 2, py + y - PLAYER_SIZE / 2, 0xFFFF00FF);
            y++;
        }
        x++;
    }
    raycasting(game, px, py);
}



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


void	draw_minimap(t_game *game)
{
	draw_borders(game);
	draw_player(game);
}
