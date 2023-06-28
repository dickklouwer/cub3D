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

#include "../../includes/cub3d.h"

#define MINIMAP_OFFSET_X 0;
#define MINIMAP_OFFSET_Y 0;
// #define FOV 60
// #define NUM_RAYS 60
// #define MAX_RAY_LENGTH 10000

void calculate_raycast(t_game *game, t_ray *rays, int px, int py)
{
    int ray_index;
    int i = 0;

    ray_index = -game->config.num_rays / 2;
    while (ray_index <= game->config.num_rays/2)
    {
        t_ray *ray = &rays[i];
        ray->angle = (game->player.pa + ray_index * game->config.angle_step) * (M_PI/180);
		// printf("ray->angle: %f\n", (ray->angle * (180 / M_PI)) - game->player.pa);
		// printf("angle_step: %f\n", game->config.angle_step);
        ray->dx = cos(ray->angle);
        ray->dy = sin(ray->angle);
        ray->length = 0;
        while (ray->length < MAX_RAY_LENGTH)
        {
            ray->px = px + ray->length * ray->dx;
            ray->py = py + ray->length * ray->dy;
			if (game->map.show_minimap)
				mlx_put_pixel(game->img, ray->px, ray->py, 0xFFFF00FF);
            if (ray->px / game->config.tile_size >= 0 && ray->px / game->config.tile_size < game->map.width && ray->py / game->config.tile_size >= 0 && ray->py / game->config.tile_size < game->map.height)
            {
                if (game->map.map[ray->py / game->config.tile_size][ray->px / game->config.tile_size] == '1')
                    break;
            }
            ray->length += 1;
        }
		// printf("ray->length: %f\n", ray->length);
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
	while (i <= game->config.num_rays)
	{
		ray = &rays[i];
		// if (game->map.show_minimap)
			// mlx_put_pixel(game->img, ray->px, ray->py, 0xFFFF00FF);
		draw_wals(game, ray);
		i++;
	}
}
