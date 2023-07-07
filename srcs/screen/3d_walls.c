/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3d_walls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:55:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/29 17:19:11 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	range(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	draw_wals(t_game *game, t_ray *ray)
{
	int	x;
	int	x_start;
	int	x_end;
	int	y;
	int	y_start;
	int	y_end;
	int	wall_height;

	ray->length *= cos(ray->angle * (M_PI / 180));
	wall_height = (game->config.tile_size / ray->length) * ((GAME_WIDTH / 2) / tan((game->config.fov / 2) * (M_PI / 180)));
	x_start = (ray->angle + (game->config.fov / 2)) * (GAME_WIDTH / game->config.fov);
	x_end = x_start + (GAME_WIDTH / game->config.num_rays);
	printf("ray->angle: %f\n", ray->angle);
	printf("x_start: %d\n", x_start);
	printf("x_end: %d\n", x_end);
	printf("wall_height: %d\n", wall_height);
	x = x_start;
	while (x <= x_end)
	{
		y_start = (GAME_HEIGTH / 2) - (wall_height / 2);
		y_end = y_start + wall_height;
		y = y_start;
		while (y <= y_end)
		{
			mlx_put_pixel(game->img, range(x, 0, GAME_WIDTH - 1), range(y, 0, GAME_HEIGTH - 1), 0xCCCCCCFF);
			y++;
		}
		x++;
	}
}
