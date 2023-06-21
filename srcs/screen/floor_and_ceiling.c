/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_and_ceiling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 11:54:54 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/21 12:47:20 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_collor_3d_array(int rgb[3])
{
	int	rgba;

	rgba = 0;
	rgba += rgb[0] << 24;
	rgba += rgb[1] << 16;
	rgba += rgb[2] << 8;
	rgba += 0x000000FF;
	return (rgba);
}

void	draw_floor_and_cailing(t_game *game)
{
	int	floor_color;
	int	ceiling_color;
	int	x;
	int	y;

	floor_color = get_collor_3d_array(game->config.floor_color);
	ceiling_color = get_collor_3d_array(game->config.ceiling_color);
	x = 0;
	while (x < GAME_WIDTH)
	{
		y = 0;
		while (y < GAME_HEIGTH)
		{
			if (y < GAME_HEIGTH / 2)
				mlx_put_pixel(game->img, x, y, ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, floor_color);
			if (game->map.show_minimap && x < 200 && y < 200)
				mlx_put_pixel(game->img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

