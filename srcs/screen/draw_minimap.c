/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/21 21:24:07 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		while (y < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, \
				(MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2) + x, \
				(MINIMAP_HEIGTH / 2) - (PLAYER_SIZE / 2) + y, \
				0xFFFF00FF);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < 10)
	{
		mlx_put_pixel(game->img, \
			(MINIMAP_WIDTH / 2) + (x * game->player.pdx), \
			(MINIMAP_HEIGTH / 2) + (x * game->player.pdy), \
			0xFFFF00FF);
		x++;
	}
}

void	draw_minimap_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < 300)
	{
		y = 0;
		while (y < 300)
		{
			if (y < 0 || y > TILE_SIZE || x < 0 || x > TILE_SIZE)
				mlx_put_pixel(game->minimap, x, y, 0x202020FF);
			else
				mlx_put_pixel(game->minimap, x, y, 0xAAAAAAFF);
			y++;
		}
		x++;
	}
}

void	draw_2d_map(t_game *game)
{
	draw_minimap_walls(game);
	draw_player(game);
}
