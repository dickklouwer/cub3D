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

void	calculate_raycast(t_game *game, t_ray *rays, int px, int py)
{
	int ray_index;
	int i = 0;

	ray_index = -game->config.num_rays / 2;
	while (ray_index <= game->config.num_rays / 2)
	{
		t_ray *ray = &rays[i];
		ray->angle = (game->player.pa + ray_index * game->config.angle_step) * (M_PI/180);
		// ray->angle = (game->player.pa - (game->config.fov / 2) + (ray_index * game->config.angle_step));
		ray->dx = cos(ray->angle);
		ray->dy = sin(ray->angle);
		// ray->dx = cos(ray->angle * M_PI);
		// ray->dy = sin(ray->angle * M_PI);
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
			// ray->length += .005;
			ray->length += 1;
		}
		ray->angle = (ray->angle * (180 / M_PI)) - game->player.pa;
		// ray->angle = ray->angle - game->player.pa;
		// printf(WHITE"=-=-=-=-Calculate-=-=-=\n"NC);
		// printf(GRAY"player.pa: %f\n"NC, game->player.pa);
		// printf(GREEN"ray->angle: %f\n"NC, ray->angle);
		// printf(YELLOW"ray->length: %f\n"NC, ray->length);
		ray_index++;
		i++;
	}
	printf("ray angle: %f\n", rays[0].angle * 180 / M_PI);
	// printf("ray angle: %f\n", rays[game->config.num_rays].angle * 180 / M_PI);
	printf("ray dx: %f\n", rays[0].dx);
	printf("ray dy: %f\n", rays[0].dy);
}

void	calculate_raycast_new(t_game *game, t_ray *rays, int px, int py)
{
	t_ray	*ray;
	int		ray_index;

	ray_index = 0;
	// printf("x:y %d:%d\n", px, py);
	while (ray_index <= game->config.num_rays)
	{
		ray = &rays[ray_index];
		ray->angle = (game->player.pa - (game->config.fov / 2) + (ray_index * game->config.angle_step));
		ray->dx = cos(ray->angle * M_PI / 180);
		ray->dy = sin(ray->angle * M_PI / 180);
		// printf(GREEN"ray->angle: %f\n"NC, ray->angle * 180 / M_PI);
		ray_index++;
	}
	printf("ray angle: %f\n", rays[60].angle);
	// printf("ray angle: %f\n", rays[game->config.num_rays].angle * 180 / M_PI);
	printf("ray dx: %f\n", rays[60].dx);
	printf("ray dy: %f\n", rays[60].dy);
}

void	draw_raycast(t_game *game, t_ray *rays)
{
	t_ray	*ray;
	int		ray_index;

	ray_index = 0;
	while (ray_index <= game->config.num_rays) 
	{
		ray = &rays[ray_index];
		if (game->map.show_minimap)
			mlx_put_pixel(game->img, ray->px, ray->py, 0x00FF00FF);
		draw_wals(game, ray);
		ray_index++;
	}
}
