/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3d_walls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:55:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/22 16:35:15 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/// @brief 
/// @param game the game struct
/// @param distance the distance to the wall
/// @param angle the relative angle for the player
void	draw_walls(t_game *game, float distance, double angle)
{
	int		i;
	int		x;
	int		y;
	int		casted_rays;
	int		scale;
	int		wall_height;

	wall_height = GAME_HEIGTH / distance * TILE_SIZE / 4;
	if (wall_height > GAME_HEIGTH)
		wall_height = GAME_HEIGTH;
	if (wall_height < 0)
		wall_height = 0;
	casted_rays = game->player.view_angle / game->player.angle_step;
	scale = GAME_WIDTH / casted_rays;
	i = 0;
	x = (angle * scale) + (GAME_WIDTH / 2);
	while (i < scale && x + i < GAME_WIDTH)
	{
		y = 0;
		while (y < wall_height * 2)
		{
			mlx_put_pixel(game->img, x + i, (GAME_HEIGTH / 2) - (wall_height) + y, 0x202020FF);
			y++;
		}
		i++;
	}
}

void	temp_test_draw_walls(t_game *game)
{
	double	angle;
	double	distance;

	game->player.view_angle = 60;
	game->player.angle_step = 1;
	distance = (1 * TILE_SIZE) + (TILE_SIZE / 2);
	angle = -30;
	while (angle <= 30)
	{
		draw_walls(game, distance, angle);
		angle += 1.0;
	}
}
