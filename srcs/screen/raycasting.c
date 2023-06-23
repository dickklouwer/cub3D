// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   raycasting.c                                       :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/06/23 10:32:15 by tklouwer      #+#    #+#                 */
// /*   Updated: 2023/06/23 10:42:01 by tklouwer      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;
#define FOV 60
#define NUM_RAYS 60
#define MAX_RAY_LENGTH 10000

void calculate_raycast(t_game *game, t_ray *rays, int px, int py)
{
    int ray_index;
    int i = 0;

    ray_index = -NUM_RAYS / 2;
    while (ray_index <= NUM_RAYS/2) 
    {
        t_ray *ray = &rays[i];
        ray->angle = (game->player.pa + ray_index * FOV / NUM_RAYS) * (M_PI/180);
        ray->dx = cos(ray->angle);
        ray->dy = sin(ray->angle);
        ray->length = 0;
        while (ray->length < MAX_RAY_LENGTH)
        {
            ray->px = px + ray->length * ray->dx;
            ray->py = py + ray->length * ray->dy;
			if (game->map.show_minimap)
				mlx_put_pixel(game->img, ray->px, ray->py, 0xFFFF00FF);
            if (ray->px / TILE_SIZE >= 0 && ray->px / TILE_SIZE < game->map.width && ray->py / TILE_SIZE >= 0 && ray->py / TILE_SIZE < game->map.height)
            {
                if (game->map.map[ray->py / TILE_SIZE][ray->px / TILE_SIZE] == '1')
                    break;
            }
            ray->length++;
        }
        ray->angle = (ray->angle * (180 / M_PI)) - game->player.pa;
        ray_index++;
        i++;
    }
}

void draw_raycast(t_game *game, t_ray *rays)
{
    t_ray *ray;
    int i;

    i = 0;
    while (i < NUM_RAYS)
    {
        ray = &rays[i];
        if (game->map.show_minimap)
            mlx_put_pixel(game->img, ray->px, ray->py, 0xFFFF00FF);
        draw_walls(game, ray->length, ray->angle);
        i++;
    }
}
