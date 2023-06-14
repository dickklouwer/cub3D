/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 11:58:05 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/06/14 20:17:00 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_screen(t_game *game)
{
	game->img = mlx_new_image(game->mlx, GAME_WIDTH, GAME_HEIGTH);
	if (!game->img || (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0))
		err_exit("Failed to draw screen");
	draw_floor_and_cailing(game);
}
