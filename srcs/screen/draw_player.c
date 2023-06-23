/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 11:56:42 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/23 15:57:50 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void calculate_player(t_game *game, t_ray *rays, int px, int py)
{
	int x;
	int y;

	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		while (y < PLAYER_SIZE)
			y++;
		x++;
	}
	calculate_raycast(game, rays, px, py);
}

void    draw_player(t_game *game, t_ray *rays, int px, int py)
{
    int x;
	int y;

	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		while (y < PLAYER_SIZE)
		{
			if (game->map.show_minimap)
				mlx_put_pixel(game->img, px + x - PLAYER_SIZE / 2, py + y - PLAYER_SIZE / 2, 0xFFFF00FF);
			y++;
		}
		x++;
	}
	draw_raycast(game, rays);
}
