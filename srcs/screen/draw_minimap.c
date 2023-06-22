/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 17:58:44 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;
#define FOV 60
#define NUM_RAYS 60
#define MAX_RAY_LENGTH 10000

void    raycasting(t_game *game, t_ray *ray, int px, int py)
{
    int ray_index;
	int relative_angle;

    ray_index = -NUM_RAYS / 2;
    while (ray_index <= NUM_RAYS/2) 
    {
        ray->angle = (game->player.pa + ray_index * FOV / NUM_RAYS) * (M_PI/180);
        ray->dx = cos(ray->angle);
        ray->dy = sin(ray->angle);
        ray->length = 0;
        while (ray->length < MAX_RAY_LENGTH)
        {
            ray->px = px + ray->length * ray->dx;
            ray->py = py + ray->length * ray->dy;
            mlx_put_pixel(game->img, ray->px, ray->py, 0xFFFF00FF);
            if (game->map.map[ray->py / TILE_SIZE][ray->px / TILE_SIZE] == '1')
                break;
            ray->length++;
        }
		relative_angle = (ray->angle * (180 / M_PI)) - game->player.pa;
        draw_walls(game, ray->length, relative_angle);
        ray_index++;
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
    raycasting(game, game->ray, px, py);
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
