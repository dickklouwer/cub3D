/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3d_walls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:55:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/17 15:53:20 by bprovoos      ########   odam.nl         */
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

	// ray->length *= cos((ray->angle - 0) * M_PI / 180);
	ray->length *= cos((ray->angle - 0) * M_PI / 180);
	wall_height = (game->config.tile_size / ray->length) * ((GAME_WIDHT / 2) / tan((game->config.fov / 2) * (M_PI / 180)));
	// wall_height = game->config.tile_size / ray->length * 1000;
	x_start = (ray->angle + (game->config.fov / 2)) * (GAME_WIDHT / game->config.fov);
	x_end = x_start + (GAME_WIDHT / game->config.num_rays);
	// printf(WHITE"=-=-=-=-=-Draw-=-=-=-=-=\n"NC);
	// printf(GREEN"ray->angle: %f\n"NC, ray->angle);
	// printf(YELLOW"ray->length: %f\n"NC, ray->length);
	// printf(BLUE"x_start: %d\n"NC, x_start);
	// printf(MAGENTA"x_end: %d\n"NC, x_end);
	// printf(CYAN"wall_height: %d\n"NC, wall_height);
	x = x_start;
	while (x <= x_end)
	{
		y_start = (GAME_HEIGHT / 2) - (wall_height / 2);
		y_end = y_start + wall_height;
		y = y_start;
		while (y <= y_end)
		{
			mlx_put_pixel(game->img, range(x, 0, GAME_WIDHT - 1), range(y, 0, GAME_HEIGHT - 1), 0xCCCCCCFF);
			y++;
		}
		x++;
	}
}
