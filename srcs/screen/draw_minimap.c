/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:41:06 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/21 16:30:11 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_game *game)
{
	int	x;
	int	y;

	x = MINIMAP_WIDTH - (PLAYER_SIZE / 2);
	while (x < MINIMAP_WIDTH + (PLAYER_SIZE / 2))
	{
		y = MINIMAP_HEIGTH - (PLAYER_SIZE / 2);
		while (y < MINIMAP_HEIGTH + (PLAYER_SIZE / 2))
		{
			mlx_put_pixel(game->img, x, y, 0xFFFF00FF);
			y++;
		}
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
			if (y < 150 || y > 175 || x < 150 || x > 175)
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
